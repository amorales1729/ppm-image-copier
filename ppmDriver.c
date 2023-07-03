#include <stdio.h>
#include "ppmUtil.h"

// first command line arg is input image. second is output.ppm file
int main(int argc, const char * argv[]) {

    FILE *myFile = fopen(argv[1], "rb");
    FILE *out = fopen(argv[2], "wb");

    pixel_t *pixel;
    header_t header;

    pixel = read(myFile, &header);
    write(out, header, pixel);
    freeMemory(pixel);
    fclose(myFile);
    fclose(out);
}

