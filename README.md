# LSB Steganography in C

This project implements **Least Significant Bit (LSB) Steganography**
to hide and retrieve secret data inside a BMP image using the C programming language.

The project is divided into **two independent modules**:
- Encoding
- Decoding

Each module follows a clean, modular design and uses a shared protocol.

---

##  Project Structure

LSB-Steganography/
│
├── Encode-Project/
│ ├── encode.c
│ ├── encode.h
│ ├── test_encode.c
│ ├── common.h
│ ├── types.h
│ └── README.md
│
├── Decode-Project/
│ ├── decode.c
│ ├── decode.h
│ ├── test_decode.c
│ ├── common.h
│ ├── types.h
│ └── README.md
│
└── README.md


##  Encoding Protocol

The encoder hides data in the following order:

1. BMP Header (copied unchanged)
2. Magic String (`#*`)
3. Secret File Size (32 bits)
4. Secret File Data
5. Remaining Image Data



## Decoding Protocol

The decoder extracts data using the same order:

1. Reads BMP pixel offset from header
2. Verifies magic string
3. Reads secret file size
4. Extracts secret file data

Build & Run

### Encoding

cd Encode-Project
gcc encode.c test_encode.c -o encode
./encode -e beautiful.bmp secret.txt stego.bmp

## Decoding

cd Decode-Project
gcc decode.c test_decode.c -o decode
./decode -d stego.bmp
