#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "common.h"

/* Read BMP pixel data offset */
uint get_bmp_pixel_offset(FILE *fptr)
{
    unsigned char b[4];

    fseek(fptr, 10, SEEK_SET);
    fread(b, 1, 4, fptr);

    return b[0] |
           (b[1] << 8) |
           (b[2] << 16) |
           (b[3] << 24);
}

/* Open required files */
Status open_files(EncodeInfo *encInfo)
{
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "rb");
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "rb");
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "wb");

    if (!encInfo->fptr_src_image ||
        !encInfo->fptr_secret ||
        !encInfo->fptr_stego_image)
    {
        return e_failure;
    }

    return e_success;
}

/* Copy BMP header */
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

/* Encode one byte into 8 image bytes */
void encode_byte_to_lsb(char data, FILE *src, FILE *dest)
{
    char img[8];

    fread(img, 1, 8, src);

    for (int i = 0; i < 8; i++)
    {
        img[i] = (img[i] & 0xFE) | ((data >> (7 - i)) & 1);
    }

    fwrite(img, 1, 8, dest);
}

/* Encode magic string */
void encode_magic_string(const char *magic, FILE *src, FILE *dest)
{
    for (int i = 0; magic[i] != '\0'; i++)
    {
        encode_byte_to_lsb(magic[i], src, dest);
    }
}

/* Encode 32-bit integer */
void encode_uint_to_lsb(uint data, FILE *src, FILE *dest)
{
    char img;

    for (int i = 31; i >= 0; i--)
    {
        fread(&img, 1, 1, src);
        img = (img & 0xFE) | ((data >> i) & 1);
        fwrite(&img, 1, 1, dest);
    }
}

/* Encode secret file data */
void encode_secret_data(FILE *secret, FILE *src, FILE *dest)
{
    char ch;

    while (fread(&ch, 1, 1, secret))
    {
        encode_byte_to_lsb(ch, src, dest);
    }
}

/* Main encoding controller */
Status do_encoding(EncodeInfo *encInfo)
{
    if (open_files(encInfo) == e_failure)
        return e_failure;

    /* Copy header */
    copy_bmp_header(encInfo->fptr_src_image,
                    encInfo->fptr_stego_image);

    /* Encode magic string */
    encode_magic_string(MAGIC_STRING,
                        encInfo->fptr_src_image,
                        encInfo->fptr_stego_image);

    /* Encode secret file size */
    fseek(encInfo->fptr_secret, 0, SEEK_END);
    uint size = ftell(encInfo->fptr_secret);
    rewind(encInfo->fptr_secret);

    encode_uint_to_lsb(size,
                       encInfo->fptr_src_image,
                       encInfo->fptr_stego_image);

    /* Encode secret file data */
    encode_secret_data(encInfo->fptr_secret,
                       encInfo->fptr_src_image,
                       encInfo->fptr_stego_image);

    /* Copy remaining image bytes */
    char ch;
    while (fread(&ch, 1, 1, encInfo->fptr_src_image))
        fwrite(&ch, 1, 1, encInfo->fptr_stego_image);

    return e_success;
}
