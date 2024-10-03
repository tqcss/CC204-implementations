#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>


// Define structure for stack
typedef struct {
    int *content;   // pointer to array of integers for containing elements in stack
    int maxSize;    // size of the array being pointed by *content
    int top;        // index of the top element in the stack
} FixedStack;

FixedStack *new_FixedStack(int size) {
    // Instantiates a stack struct in memory
    FixedStack *stack = (FixedStack *)malloc(sizeof(FixedStack));

    // Initializes variables within the stack structure
    stack->content = (int *)malloc(sizeof(int) * size);
    stack->maxSize = size;
    stack->top = -1;

    return stack;
}

void delete_DynamicStack(FixedStack* stack) {
    if (stack == NULL) return;

    // Deallocates all memory relating to passed stack structure
    if (stack->content != NULL) {
        free(stack->content);
    }
    free(stack);
}

bool isEmpty(FixedStack *stack) {
    return stack->top == -1;
}

bool isFull(FixedStack *stack) {
    return stack->top == stack->maxSize - 1;
}

void push(FixedStack *stack, int element) {
    if (isFull(stack)) {
        printf("Stack Overflow.\n");
        return;
    }
    stack->content[++stack->top] = element;
}

int pop(FixedStack *stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow.\n");
        return INT_MIN;
    }
    return stack->content[stack->top--];
}

int peek(FixedStack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return INT_MIN;
    }
    return stack->content[stack->top];
}
