#include "stack.h"



void push(stack_elem **stack, int i, int j){
    stack_elem *tmp = malloc(sizeof(stack_elem));
    (*tmp) = (stack_elem) {i, j, (*stack)};
    (*stack) = tmp;
    return;
}

stack_elem pop(stack_elem **stack){
    stack_elem *tmp = (*stack);
    if (!tmp)
        return (stack_elem) {-1, -1, NULL};
    int i = tmp->i, j = tmp->j;
    (*stack) = (*stack)->next;
    free(tmp);
    return (stack_elem) {i, j, NULL};
}