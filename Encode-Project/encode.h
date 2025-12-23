#ifndef ENCODE_H
#define ENCODE_H

#include <stdio.h>
#include "types.h"

typedef struct _EncodeInfo
{
    char *src_image_fname;
    char *secret_fname;
    char *stego_image_fname;

    FILE *fptr_src_image;
    FILE *fptr_secret;
    FILE *fptr_stego_image;

} EncodeInfo;

Status do_encoding(EncodeInfo *encInfo);
Status open_files(EncodeInfo *encInfo);
Status copy_bmp_header(FILE *src, FILE *dest);
uint get_bmp_pixel_offset(FILE *fptr);

#endif
