#ifndef FILTERS_H
#define FILTERS_H

#include "image.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void gaussian_blur(struct pixel_wb **image_wb, int height, int width);
void sober_filter(struct pixel_wb **image_wb, int height, int width);
void add_contrast(struct pixel_wb **image_wb, int height, int width, int max_c, int min_c);
#endif