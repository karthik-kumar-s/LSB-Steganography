#ifndef DECODE_H
#define DECODE_H

#include <stdio.h>
#include <string.h>
#include "types.h"
#include "common.h"

/* Structure to store decoding related data */
typedef struct _DecodeInfo
{
    FILE *fptr_stego_image;
    FILE *fptr_output;

    char *stego_image_fname;

    uint secret_file_size;

} DecodeInfo;

/* Function prototypes */
Status do_decoding(DecodeInfo *decInfo);
Status open_files(DecodeInfo *decInfo);
Status decode_lsb_to_byte(char *data, FILE *fptr);
Status decode_magic_string(DecodeInfo *decInfo);
Status decode_secret_file_size(DecodeInfo *decInfo);
Status decode_secret_file_data(DecodeInfo *decInfo);

#endif
