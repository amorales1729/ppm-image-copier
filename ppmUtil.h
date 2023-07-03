#ifndef PPMUTIL_H
#define PPMUTIL_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Pixel{
    unsigned char r, g, b;
}pixel_t;

typedef struct Header{
    char type[3];
    unsigned int width;
    unsigned int height;
    unsigned int maxVal;
}header_t;

void readHeader(FILE* , header_t* );
pixel_t* readPixels(FILE* , header_t );
void writeHeader(FILE* , header_t );
void writePixels(FILE* , pixel_t*, header_t );
pixel_t* read(FILE* , header_t* );
void write(FILE* , header_t, pixel_t* );
pixel_t* allocatePixMemory(header_t);
void freeMemory(pixel_t*);
void ckComment(FILE*);

#endif