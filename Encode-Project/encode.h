#ifndef ENCODE_H
#define ENCODE_H

#include <stdio.h>
#include "types.h"

/* Structure to hold encoding information */
typedef struct _EncodeInfo
{
    char *src_image_fname;
    char *secret_fname;
    char *stego_image_fname;

    FILE *fptr_src_image;
    FILE *fptr_secret;
    FILE *fptr_stego_image;

} EncodeInfo;

/* Function prototypes */
uint get_bmp_pixel_offset(FILE *fptr);
Status open_files(EncodeInfo *encInfo);
Status copy_bmp_header(FILE *src, FILE *dest);

void encode_byte_to_lsb(char data, FILE *src, FILE *dest);
void encode_magic_string(const char *magic, FILE *src, FILE *dest);
void encode_uint_to_lsb(uint data, FILE *src, FILE *dest);
void encode_secret_data(FILE *secret, FILE *src, FILE *dest);

Status do_encoding(EncodeInfo *encInfo);

#endif
