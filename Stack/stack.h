#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#define MAXSTACK 10

typedef struct stack {
    float array[MAXSTACK];  // Changed int to float
    size_t top;
} stack;

typedef struct min_stack {
    float array[MAXSTACK];  // Changed int to float
    size_t top;
} min_stack;

void createstack(stack *ps);
int stackfull(stack *ps);
int stackempty(stack *ps);
void push(float e, stack *ps);
float pop(stack *ps);
float stacktop(stack *ps);
float findMin();

#endif
