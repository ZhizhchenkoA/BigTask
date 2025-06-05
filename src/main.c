#include "main.h"

int main() {
    
    int width, height;
    char* filename = "img/input4.png";
    struct pixel **image;
    int i;

    // Загрузка изображения
    int error = read_png(&image, &width, &height, filename);
    if (error) {
        printf("Ошибка загрузки изображения %s: %s\n", filename, lodepng_error_text(error));
        return 1;
    }
    
    printf("Изображение загружено: %ux%u пикселей\n", width, height);

    struct pixel_wb **image_wb = malloc(sizeof(pixel_wb*) * height);
    for (i = 0; i < height; i++)
        image_wb[i] = malloc(sizeof(pixel_wb) * width);
    
    convert_to_wb(image, height, width, image_wb);
    gaussian_blur(image_wb, height, width);
    sober_filter(image_wb, height, width);

    add_contrast(image_wb, height, width, 150, 20);
   
    // write_png_wb(image_wb, height, width, "img/out1.png");
    // add_contrast(image_wb, height, width, 200, 50);
    // write_png_wb(image_wb, height, width, "img/out2.png");
    // sober_filter(image_wb, height, width);
    // write_png_wb(image_wb, height, width, "img/out3.png");
    // add_contrast(image_wb, height, width, 210, 20);
    // gaussian_blur(image_wb, height, width);

    int n = connected_components(image_wb, height, width, 20);
    printf("Количество компонент связности %d\n", n);
    int *components_arr = calloc(n, sizeof(int));

    count_pixel_in_components(image_wb, height, width, components_arr);
    write_png_color(image_wb, height, width, components_arr, 50, "img/output4.png");

    free(components_arr);
    for (i = 0; i < height; i++)
        free(image[i]);
    free(image);

    for (i = 0; i < height; i++)
        free(image_wb[i]);
    free(image_wb);
    return 0;
}