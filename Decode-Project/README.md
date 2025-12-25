# Decode Project – LSB Steganography

This module is responsible for **extracting hidden data** from a BMP image
that was encoded using the **Least Significant Bit (LSB)** steganography technique.

The decoding logic strictly follows the same protocol used by the encoding module.

---

##  Decoding Protocol

The decoder reads data from the stego image in the following order:

1. **BMP Header**
   - The actual pixel data offset is read from the BMP header
   - Decoding starts exactly at the pixel data location

2. **Magic String**
   - A predefined marker (`#*`)
   - Used to verify whether the image contains hidden data

3. **Secret File Size**
   - A 32-bit integer
   - Represents the number of bytes in the hidden file

4. **Secret File Data**
   - Each byte is reconstructed from the LSBs of 8 image bytes
   - Written to an output file named `decoded.txt`

---

##  Files

- `decode.c` – Core decoding logic
- `decode.h` – Structure definitions and function prototypes
- `test_decode.c` – Entry point (`main`)
- `common.h` – Shared constants (magic string, BMP details)
- `types.h` – Common type definitions

---

##  Build Instructions

Compile the decoder using:

gcc decode.c test_decode.c -o decode

Run:
./decode -d stego.bmp
