#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>


typedef struct Node {
    int value;
    struct Node *next
} Node;

Node *new_Node(int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    
    node->value = value;
    node->next = NULL;

    return node;
} Node;


typedef struct {
    Node *head;
    int size;
} DynamicStack;

DynamicStack *new_DynamicStack() {
    DynamicStack *stack = (DynamicStack *)malloc(sizeof(DynamicStack));

    stack->head = NULL;
    stack->size = 0;

    return stack;
}

void delete_DynamicStack(DynamicStack *stack) {
    if (stack == NULL) return;

    Node *current = stack->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(stack);
}

bool isEmpty(DynamicStack* stack) {
    return stack->size == 0;
}

void push(DynamicStack *stack, int element) {
    Node *newNode = new_Node(element);
    newNode->next = stack->head;

    stack->head = newNode;
    stack->size++;
}


int pop(DynamicStack *stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow.\n");
        return INT_MIN;
    }
    Node *temp = stack->head;
    int topValue = temp->value;

    stack->head = stack->head->next;
    stack->size--;

    free(temp);
    return topValue;
}

int peek(DynamicStack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return INT_MIN;
    }
    return stack->head->value;
}
