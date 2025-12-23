#include <stdio.h>
#include <string.h>
#include "encode.h"

int main(int argc, char *argv[])
{
    EncodeInfo encInfo;

    if (argc != 5)
    {
        printf("Usage: ./encode -e <src.bmp> <secret.txt> <stego.bmp>\n");
        return 1;
    }

    encInfo.src_image_fname = argv[2];
    encInfo.secret_fname = argv[3];
    encInfo.stego_image_fname = argv[4];

    if (do_encoding(&encInfo) == e_failure)
    {
        printf("Encoding failed\n");
        return 1;
    }

    printf("Encoding successful\n");
    return 0;
}
