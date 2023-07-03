#include "ppmUtil.h"

// header_t – represents the header data of the input image.
// Returns the pixel_t pointer created for readPixels.
pixel_t* read(FILE* input, header_t* header) {

    readHeader(input, header);
    pixel_t *pixel = readPixels(input, *header);
    return pixel;
}

// this function will read in each of the 4 parts of the header of a ppm image.
// reads one part of the header then calls a function to check for comments.
void readHeader(FILE* input, header_t* header){

    char *string;
    fscanf(input, "%s", header->type);
    ckComment(input);
    fscanf(input, "%s", string);
    header->width = atoi(string);
    ckComment(input);
    fscanf(input, "%s",string);
    header->height = atoi(string);
    ckComment(input);
    fscanf(input, "%s", string);
    header->maxVal = atoi(string);
    ckComment(input);
}

// read in the pixels for the image.
// call the function allocatePixMemory to allocate the memory for the pixels.
// use fread to read the pixels storing them in the allocated memory,
// then return the allocated memory.
pixel_t* readPixels(FILE* input, header_t header){

    pixel_t *pixel = allocatePixMemory(header);
    fread(pixel, sizeof(unsigned char),
          header.width * header.height * 3, input);
    return pixel;
}

// pixel_t – contains the pixel data to be written.
// calls a header and pixel function to store the data into new image (output)
void write(FILE* output, header_t header, pixel_t* pixel){

    writeHeader(output, header);
    writePixels(output, pixel, header);
}

// writes header information to the output file
void writeHeader(FILE* output, header_t header){

    fprintf(output, "%s\n%d %d %d\n", header.type, header.width,
            header.height, header.maxVal);
}

// writes pixel data into output file
void writePixels(FILE* output, pixel_t* pixel, header_t header){

    fwrite(pixel, sizeof(unsigned char),
           header.width * header.height * 3, output);
}

// allocates memory for the pixels of the image
// and returns the allocated memory.
pixel_t* allocatePixMemory(header_t header){

    pixel_t *pixel = (pixel_t*) malloc(header.width * header.height * 3);
    if (pixel == NULL) {
        fprintf(stderr, "Error: could not allocate memory for pixel data.\n");
        return NULL;
    }
    return pixel;
}

// frees memory
void freeMemory(pixel_t* pixel){

    free(pixel);
}

// checks for and ignores any comments in the ppm header.
void ckComment(FILE* input){

    char c = fgetc(input);
    if (c == ' ' || c == '\n'){
        c = fgetc(input);
    }
    while (c == '#') {
        char comment[1024];
        fgets(comment, 1024, input);
        c = fgetc(input);
    }
    fseek(input, -1, SEEK_CUR);
}