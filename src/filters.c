#include "filters.h"


void gaussian_blur(struct pixel_wb **image_wb, int height, int width){
    int i, j, dx, dy;
    float gauss[3][3] = {
        {0.064, 0.084, 0.064},
        {0.084, 0.084, 0.084},
        {0.064, 0.084, 0.064}
    };
    struct pixel_wb **image_copy = copy_image_wb(image_wb, height, width);
    double color;
    for (i = 1; i < height - 1; i++)
        for (j = 1; j < width - 1; j++){
            color = 0;
            for (dx = -1; dx <= 1; dx++)
                for (dy = -1; dy <= 1; dy++)
                    color += (double)(image_copy[i + dx][j + dy].c) * gauss[dx + 1][dy + 1];
            image_wb[i][j].c = color;
        }
    for (i = 0; i < height; i++)
       free(image_copy[i]);
    free(image_copy);  
    return;
}

void sober_filter(struct pixel_wb **image_wb, int height, int width){
    struct pixel_wb **image_copy = copy_image_wb(image_wb, height, width);
    int gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int gy[3][3] = {
        {1, 2, 1},
        {0, 0, 0},
        {-1, -2, -1}
    };

    int i, j, grad, dx, dy, color, sx, sy;
    for (i = 1; i < height - 1; i++)
        for (j = 1; j < width - 1; j++){
            sx = 0;
            sy = 0;
            for (dx = -1; dx <= 1; dx++)
                for (dy = -1; dy <= 1; dy++){
                    color = image_copy[i + dx][j + dy].c;
                    sx += color * gx[dx + 1][dy + 1];
                    sy += color * gy[dx + 1][dy + 1];
                }
            grad = (int) (sqrt(sx * sx + sy * sy));
            if (grad > 255)
                grad = 255;
            else if (grad < 0)
                grad = 0;
            image_wb[i][j].c = grad;
        }
    for (i = 0; i < height; i++)
       free(image_copy[i]);
    free(image_copy);
    return;
}

void add_contrast(struct pixel_wb **image_wb, int height, int width, int max_c, int min_c){
    int i, j;
    for (i = 0; i < height; i++)
        for (j = 0; j < width; j++)
            if (image_wb[i][j].c >= max_c)
                image_wb[i][j].c = 255;
            else if(image_wb[i][j].c <= min_c)
                image_wb[i][j].c = 0;
    return;
}
