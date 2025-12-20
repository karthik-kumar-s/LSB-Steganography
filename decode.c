#include "decode.h"

// Main decoding controller 
Status do_decoding(DecodeInfo *decInfo)
{
    // This will be implemented step by step
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
