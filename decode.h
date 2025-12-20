#ifndef DECODE_H
#define DECODE_H

#include <stdio.h>
#include <string.h>
#include "types.h"
#include "common.h"

// Structure to store decoding related data
typedef struct _DecodeInfo
{
    FILE *fptr_stego_image;
    FILE *fptr_output;

    char *stego_image_fname;
    char output_fname[50];

    uint secret_file_size;
    uint extn_size;
    char secret_extn[10];

} DecodeInfo;

// Function prototypes
Status do_decoding(DecodeInfo *decInfo);
Status open_files(DecodeInfo *decInfo);

#endif
