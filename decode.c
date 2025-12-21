#include "decode.h"

// Main decoding controller
Status do_decoding(DecodeInfo *decInfo)
{
    // Open stego image
    if (open_files(decInfo) == e_failure)
        return e_failure;

    // Skip BMP header (first 54 bytes)
    fseek(decInfo->fptr_stego_image, BMP_HEADER_SIZE, SEEK_SET);

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
        fread(&image_byte, 1, 1, fptr);          // Read one image byte
        *data = (*data << 1) | (image_byte & 1); // Collect LSB
    }
    return e_success;
}

// Decode and verify magic string
Status decode_magic_string(DecodeInfo *decInfo)
{
    char magic[strlen(MAGIC_STRING) + 1];

    for (int i = 0; i < strlen(MAGIC_STRING); i++)
    {
        decode_lsb_to_byte(&magic[i], decInfo->fptr_stego_image);
    }

    magic[strlen(MAGIC_STRING)] = '\0';

    if (strcmp(magic, MAGIC_STRING) != 0)
        return e_failure;

    return e_success;
}
