#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

struct stack_elem{
    int i, j;
    struct stack_elem *next;
};

typedef struct stack_elem stack_elem;
void push(stack_elem **stack, int i, int j);
stack_elem pop(stack_elem **stack);

#endif