#include "image.h"


int read_png(struct pixel ***image, int *width, int *height, char *filename){
    int error;
    unsigned char* image_char = NULL;
    error = lodepng_decode32_file(&image_char, width, height, filename);
    if (error) 
        return 1;
    int i;
    *image = malloc(sizeof(pixel*) * (*height));
    for (i = 0; i < (*height); i++)
        (*image)[i] = malloc(sizeof(pixel) * (*width));

    for (i = 0; i < (*height) * (*width) * 4; i += 4)
        (*image)[(i / 4) / (*width)][(i / 4) % (*width)] = 
            (pixel) {image_char[i], image_char[i+1], image_char[i+2], image_char[i+3]};
    free(image_char);
    return 0;
}

int convert_to_wb(struct pixel **image, int height, int width, struct pixel_wb **image_wb){
    int i, j;
    for (i = 0; i < height; i++)
        for (j = 0; j < width; j++)
            image_wb[i][j] = (pixel_wb){(unsigned char)((float)(image[i][j].r) * 0.299 + (float)(image[i][j].g) * 0.59 + (float) (image[i][j].b) * 0.11), 0};
    return 0;
}

struct pixel_wb **copy_image_wb(struct pixel_wb **image_wb, int height, int width){
    struct pixel_wb **image_copy = malloc(sizeof(pixel_wb*) * height);
    int i, j;
    for (i = 0; i < height; i++)
        image_copy[i] = malloc(sizeof(pixel_wb) * width);
    for (i = 0; i < height; i++)
        for (j = 0; j < width; j++)
            image_copy[i][j] = image_wb[i][j];
    return image_copy;
}

int write_png_wb(struct pixel_wb **image_wb, int height, int width, char *filename){
    unsigned char *image = malloc(sizeof(unsigned char) * width * height * 4);
    int i, j, idx;
    for (i = 0; i < height; i++)
        for (j = 0; j < width; j++){
            idx = (i * width + j) * 4;
            image[idx] = image[idx + 1] = image[idx + 2] = image_wb[i][j].c;
            image[idx + 3] = 255;
        }
    
    int error = lodepng_encode32_file(filename, image, width, height);
    free(image);
    return error;
}

int write_png_color(struct pixel_wb **image_wb, int height, int width, char *filename){
    unsigned char *image = malloc(sizeof(unsigned char) * width * height * 4);
    int i, j, idx, comp;
    for (i = 0; i < height; i++)
        for (j = 0; j < width; j++){
            idx = (i * width + j) * 4;
            if (image_wb[i][j].c == 255)
                image[idx] = image[idx + 1] = image[idx + 2] = 255;
            else if (image_wb[i][j].c == 0)
                image[idx] = image[idx + 1] = image[idx + 2] = 0;
            else{
                comp = image_wb[i][j].component;
                image[idx] = comp * 13 % 256;
                image[idx + 1] = comp * 29 % 256;
                image[idx + 2] = comp * 19 % 256;

            }
            image[idx + 3] = 255;
        }
    
    int error = lodepng_encode32_file(filename, image, width, height);
    free(image);   
    return error;
}