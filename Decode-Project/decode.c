#include "decode.h"

// Read BMP pixel data offset (same logic as encoder) 
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

// Main decoding controller 
Status do_decoding(DecodeInfo *decInfo)
{
    uint offset;

    // Open stego image 
    if (open_files(decInfo) == e_failure)
        return e_failure;

    // Get actual BMP pixel offset 
    offset = get_bmp_pixel_offset(decInfo->fptr_stego_image);

    // Move file pointer to start of encoded data 
    fseek(decInfo->fptr_stego_image, offset, SEEK_SET);

    // Decode and verify magic string 
    if (decode_magic_string(decInfo) == e_failure)
    {
        printf("Magic string mismatch\n");
        return e_failure;
    }

    // Decode secret file size 
    decode_secret_file_size(decInfo);
    printf("Decoded secret file size: %u bytes\n",
           decInfo->secret_file_size);

    
    decInfo->fptr_output = fopen("decoded.txt", "wb");
    if (decInfo->fptr_output == NULL)
    {
        perror("fopen");
        return e_failure;
    }

    // Decode secret file data 
    decode_secret_file_data(decInfo);

    printf("Decoding successful\n");
    return e_success;
}

// Open stego image file 
Status open_files(DecodeInfo *decInfo)
{
    decInfo->fptr_stego_image = fopen(decInfo->stego_image_fname, "rb");
    if (decInfo->fptr_stego_image == NULL)
    {
        perror("fopen");
        return e_failure;
    }
    return e_success;
}

// Decode one byte from 8 image bytes 
Status decode_lsb_to_byte(char *data, FILE *fptr)
{
    char image_byte;
    *data = 0;

    for (int i = 0; i < 8; i++)
    {
        fread(&image_byte, 1, 1, fptr);
        *data = (*data << 1) | (image_byte & 1);
    }
    return e_success;
}

// Decode and verify magic string 
Status decode_magic_string(DecodeInfo *decInfo)
{
    char magic[strlen(MAGIC_STRING) + 1];

    for (int i = 0; i < strlen(MAGIC_STRING); i++)
    {
        decode_lsb_to_byte(&magic[i],
                           decInfo->fptr_stego_image);
    }

    magic[strlen(MAGIC_STRING)] = '\0';

    if (strcmp(magic, MAGIC_STRING) != 0)
        return e_failure;

    return e_success;
}

// Decode secret file size (32 bits) 
Status decode_secret_file_size(DecodeInfo *decInfo)
{
    char image_byte;
    decInfo->secret_file_size = 0;

    for (int i = 0; i < 32; i++)
    {
        fread(&image_byte, 1, 1, decInfo->fptr_stego_image);
        decInfo->secret_file_size =
            (decInfo->secret_file_size << 1) | (image_byte & 1);
    }

    return e_success;
}

// Decode secret file data 
Status decode_secret_file_data(DecodeInfo *decInfo)
{
    char ch;

    for (uint i = 0; i < decInfo->secret_file_size; i++)
    {
        decode_lsb_to_byte(&ch,
                           decInfo->fptr_stego_image);
        fwrite(&ch, 1, 1, decInfo->fptr_output);
    }

    return e_success;
}
