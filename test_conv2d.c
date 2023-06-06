#include <stdio.h>
#include <stdlib.h>

#include "conv2d.c"

#define IMG_HEIGHT 128
#define IMG_WIDTH 64

void print_image (uint8_t *img) {
    for (int r=0;r<IMG_HEIGHT;r++) {
        for (int c=0;c<IMG_WIDTH;c++)
            printf("%02X ", img[r*IMG_HEIGHT+c]);
        printf("\n");
    }
}

int main () {

    srand((unsigned int)NULL);

    int8_t kernel[] = {
        1,2,1,
        2,4,2,
        1,2,1
    };
    uint8_t pixel;

    uint8_t* image = (uint8_t*)calloc(IMG_HEIGHT*IMG_WIDTH, sizeof(uint8_t));
    uint8_t* rslt = (uint8_t*)calloc(IMG_HEIGHT*IMG_WIDTH, sizeof(uint8_t));

    for (int r=0;r<IMG_HEIGHT;r++) {
        for (int c=0;c<IMG_WIDTH;c++) {
            pixel=0xFF-rand()%16;
            if (c<IMG_WIDTH/2)
                pixel=0x00+rand()%16;
            image[r*IMG_HEIGHT+c] = pixel;
        }
    }

    rslt = convolve_base(image,IMG_HEIGHT,IMG_WIDTH,kernel);

    printf("\n\n");
    print_image(image);
    printf("\n\n");
    print_image(rslt);
    printf("\n\n");

free_img:
    free(image);
    free(rslt);
    return 0;
}