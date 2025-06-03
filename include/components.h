#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "stack.h"

void DFS(struct pixel_wb **image_wb, int height, int width, int i, int j, int diff, int idx_component);
int connected_components(struct pixel_wb **image_wb, int height, int width, int diff);
void count_pixel_in_components(struct pixel_wb **image_wb, int height, int width, int *componets_arr);
#endif