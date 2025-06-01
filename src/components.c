#include "components.h"

void DFS(struct pixel_wb **image_wb, int height, int width, int i, int j, int diff, int idx_component){
    int arr[][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; 
    stack_elem *stack = NULL;
    stack_elem tmp_elem;
    push(&stack, i, j);
    int i_new, j_new;
    
    while (stack){
        tmp_elem = pop(&stack);
        i = tmp_elem.i;
        j = tmp_elem.j;
        image_wb[i][j].component = idx_component;
        for (int tmp = 0; tmp < 4; tmp++){
            i_new = i + arr[tmp][0];
            j_new = j + arr[tmp][1];
            if (i_new >= 0 && i_new < height && j_new >= 0 && j_new < width &&
                    image_wb[i_new][j_new].component == 0 &&
                    abs(image_wb[i][j].c - image_wb[i_new][j_new].c) <= diff)
                push(&stack, i_new, j_new);
        }
    }
    return;
}
int connected_components(struct pixel_wb **image_wb, int height, int width, int diff){
    int i, j, idx_component = 1;
    
    for (i = 0; i < height; i++)
        for (j = 0; j < width; j++)
            if (image_wb[i][j].component == 0){
                DFS(image_wb, height, width, i, j, diff, idx_component);
                idx_component++;
            }

    return idx_component;
}