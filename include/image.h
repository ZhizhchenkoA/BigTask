#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <stdlib.h>
#include "lodepng.h"

typedef struct pixel {
    unsigned char r, g, b, a;
}pixel;

typedef struct pixel_wb{
    unsigned char c;
    int component;
}pixel_wb;

int read_png(struct pixel ***image, int *width, int *height, char *filename);
int write_png_wb(struct pixel_wb **image_wb, int height, int width, char *filename);
int make_wb(struct pixel **image, int height, int width, struct pixel_wb **image_wb);
struct pixel_wb **copy_image_wb(struct pixel_wb **image_wb, int height, int width);
int write_png_wb(struct pixel_wb **image_wb, int height, int width, char *filename);
int write_png_color(struct pixel_wb **image_wb, int height, int width, char *filename);
#endif