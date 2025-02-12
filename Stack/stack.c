#include "stack.h"

// Define the min_stack globally (so no need to pass it)
static min_stack pms;  // Only one instance of min_stack

void createstack(stack *ps) {
    ps->top = 0;
    pms.top = 0;  // Initialize the min_stack
}

int stackfull(stack *ps) {
    return ps->top == MAXSTACK;
}

int stackempty(stack *ps) {
    return ps->top == 0;
}

void push(float e, stack *ps) {
    if (!stackfull(ps)) {
        ps->array[ps->top++] = e;

        if (pms.top == 0 || e <= pms.array[pms.top - 1]) {
            pms.array[pms.top++] = e;
        } else {
            pms.array[pms.top] = pms.array[pms.top - 1];
            pms.top++;
        }
    } else {
        printf("Stack is full\n");
    }
}

float pop(stack *ps) {
    if (!stackempty(ps)) {
        pms.top--;  // Pop from min_stack as well
        return ps->array[--ps->top];
    } else {
        printf("Stack is empty\n");
        return -1.0f;  // Changed return type to float
    }
}

float stacktop(stack *ps) {
    if (!stackempty(ps)) {
        return ps->array[ps->top - 1];
    } else {
        printf("Stack is empty\n");
        return -1.0f;
    }
}

float findMin() {
    if (pms.top > 0) {
        return pms.array[pms.top - 1];
    } else {
        printf("Stack is empty\n");
        return -1.0f;
    }
}
