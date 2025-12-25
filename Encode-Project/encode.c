#include <stdio.h>
#include "types.h"
#include "common.h"
#include "encode.h"

uint get_bmp_pixel_offset(FILE *fptr)
{
    unsigned char b[4];

    fseek(fptr, 10, SEEK_SET);
    fread(b, 1, 4, fptr);

    return b[0] | (b[1] << 8) | (b[2] << 16) | (b[3] << 24);
}

Status open_files(EncodeInfo *encInfo)
{
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "rb");
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "wb");

    if (!encInfo->fptr_src_image || !encInfo->fptr_stego_image)
        return e_failure;

    return e_success;
}

Status copy_bmp_header(FILE *src, FILE *dest)
{
    uint offset = get_bmp_pixel_offset(src);
    char ch;

    rewind(src);
    for (uint i = 0; i < offset; i++)
    {
        fread(&ch, 1, 1, src);
        fwrite(&ch, 1, 1, dest);
    }
    return e_success;
}

Status do_encoding(EncodeInfo *encInfo)
{
    if (open_files(encInfo) == e_failure)
        return e_failure;

    copy_bmp_header(encInfo->fptr_src_image,
                    encInfo->fptr_stego_image);

    encode_byte_to_lsb('A',
                       encInfo->fptr_src_image,
                       encInfo->fptr_stego_image);

    char ch;
    while (fread(&ch, 1, 1, encInfo->fptr_src_image))
        fwrite(&ch, 1, 1, encInfo->fptr_stego_image);

    return e_success;
}

// * Encode one character (8 bits) into 8 bytes of image data using LSB
void encode_byte_to_lsb(char data, FILE *fptr_src_image, FILE *fptr_stego_image)
{
    char image_buffer[8];

    // Read 8 bytes from source image
    fread(image_buffer, 1, 8, fptr_src_image);

    // Modify LSB of each byte
    for (int i = 0; i < 8; i++)
    {
        image_buffer[i] =
            (image_buffer[i] & 0xFE) | ((data >> (7 - i)) & 1);
    }

    // Write modified bytes to stego image
    fwrite(image_buffer, 1, 8, fptr_stego_image);
}
