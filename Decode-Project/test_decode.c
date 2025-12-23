#include "decode.h"

int main(int argc, char *argv[])
{
    DecodeInfo decInfo;

    if (argc != 3 || strcmp(argv[1], "-d") != 0)
    {
        printf("Usage: ./decode -d stego.bmp\n");
        return 1;
    }

    decInfo.stego_image_fname = argv[2];

    if (do_decoding(&decInfo) == e_failure)
    {
        printf("Decoding failed\n");
        return 1;
    }

    return 0;
}
