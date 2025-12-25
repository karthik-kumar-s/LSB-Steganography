# Encoding Project – LSB Steganography

This module encodes secret data into a BMP image using
Least Significant Bit (LSB) technique.

## Encoding Order
1. BMP Header
2. Magic String
3. Secret File Size (32-bit)
4. Secret File Data
5. Remaining Image Bytes

## Build
gcc encode.c test_encode.c -o encode

## Run
./encode -e beautiful.bmp secret.txt stego.bmp
