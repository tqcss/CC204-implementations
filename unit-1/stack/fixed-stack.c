// CODE IMPLEMENTATION FOR FIXED SIZE STACK
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define STACK_ERROR INT_MIN

// DATA STRUCTURE

typedef struct FStack
{
    int topIndex, size;
    int *bottom;
} FStack;

// Instantiates a stack with a fixed size.
FStack *FStack_create(const int size)
{
    FStack *stack = (FStack *)malloc(sizeof(FStack));
    if (!stack)
        return NULL;

    // define members
    stack->size = size;
    stack->topIndex = -1;                              // keeps track of the index of the element last added to the stack
    stack->bottom = (int *)malloc(size * sizeof(int)); // creates an integer array with desired size

    if (stack->bottom == NULL)
    {
        free(stack);
        return NULL;
    }
    *stack->bottom = 0;

    return stack;
}

// Deletes and deallocates all memory used by stack data structure.
bool FStack_delete(FStack *stack)
{
    if (!stack)
        return false;

    free(stack->bottom);
    free(stack);
    stack = NULL;
    return true;
}

// OPERATION INITIALIZATIONS

bool FStack_push(FStack *stack, const int value);
int FStack_pop(FStack *stack);
bool FStack_isEmpty(FStack *stack);
int FStack_peek(FStack *stack);
int FStack_search(FStack *stack, const int value);

// OPERATION DEFINITIONS

// Adds an element on top of stack.
bool FStack_push(FStack *stack, const int value)
{
    if (!stack)
        return false;

    if (stack->topIndex == stack->size) // checks if stack is full
    {
        return false; // failed to push element to stack as it reached its max capacity
    }
    stack->bottom[++stack->topIndex] = value;
    return true;
}

// Removes the element on top of stack and returns it.
int FStack_pop(FStack *stack)
{
    if (!stack)
        return STACK_ERROR;

    if (FStack_isEmpty(stack))
    {
        return STACK_ERROR; // no elements to pop from stack as it is empty
    }
    return stack->bottom[stack->topIndex--];
}

// Returns true if stack does not contain any element, false otherwise.
bool FStack_isEmpty(FStack *stack)
{
    if (!stack)
        return false;
    return stack->topIndex == -1;
}

// Returns the element on top of stack without modifying the stack in any way.
int FStack_peek(FStack *stack)
{
    if (FStack_isEmpty(stack))
        return STACK_ERROR;
    return stack->bottom[stack->topIndex];
}

// Searches for a specific element within the stack and returns for its
// index. If the element being searched was not found in the stack,
// the function return -1.
int FStack_search(FStack *stack, const int value)
{
    for (int index = 0; index <= stack->topIndex; ++index)
    {
        if (stack->bottom[index] == value)
            return index;
    }
    return -1;
}

// Prints out stacks elements in terminal surrounded by brackets.
bool FStack_print(FStack *stack)
{
    if (!stack) // return false if passed stack is NULL
        return false;

    if (FStack_isEmpty(stack))
    {
        printf("[]\n");
        return true;
    }

    // print each element in stack
    printf("[");
    for (int i = 0; i < stack->topIndex; ++i)
    {
        printf("%i, ", stack->bottom[i]);
    }
    printf("%i]\n", stack->bottom[stack->topIndex]);
    return true;
}

/*
int main()
{
    const char commands[] = "[COMMANDS]\n0 - help\n1 - new\n2 - display\n3 - size\n4 - isempty\n5 - push\n6 - pop\n7 - peek\n8 - search\n";
    FStack *stack = NULL;
    int response = 0;

    printf("%s", commands);
    while (true)
    {

        printf("> ");
        if (scanf("%i", &response) != 1)
        {
            int inputBuffer;
            while ((inputBuffer = getchar()) != '\n' && inputBuffer != EOF) {};
            printf("Invalid input: Expected an integer.\n");
            continue;
        }

        switch (response)
        {
        // help
        case 0:
            printf("%s", commands);
            break;

        // new
        case 1:
            int size = -1;

            if (stack)
            {
                FStack_delete(stack);
            }

            printf("Creating a new stack. ");
            while (true)
            {
                printf("Enter the size of the stack. (Enter 0 to cancel this process.)\n> ");
                if (scanf("%i", &size) != 1)
                {
                    int inputBuffer;
                    while ((inputBuffer = getchar()) != '\n' && inputBuffer != EOF) {};
                    printf("Invalid input: Expected an integer.\n");
                    continue;
                }

                if (size == 0)
                {
                    printf("Stack creation cancelled.\n");
                    break;
                }
                if (size < 0)
                {
                    printf("Invalid input: Size of the stack cannot be negative integer.\n");
                    continue;
                }

                stack = FStack_create(size);
                if (stack)
                {
                    printf("Successfully created stack with the size of [%i].\n", size);
                    break;
                }
                printf("Failed to allocate enough memory for stack.\n");
                break;
            }
            break;

        // display
        case 2:
            if (FStack_print(stack))
                break;

            printf("Unable to display stack. Stack cannot be found.\n");
            break;

        // size
        case 3:
            if (stack)
            {
                printf("%i\n", stack->size);
                break;
            }
            printf("Unable to get stack's size. Stack cannot be found.\n");
            break;

        // isEmpty
        case 4:
            printf("%s", FStack_isEmpty(stack) ? "true\n" : "false\n");
            break;

        // push
        case 5:
            int element;

            while (true)
            {
                printf("Enter the element to be pushed in the stack.\n> ");
                if (scanf("%i", &element) != 1)
                {
                    int inputBuffer;
                    while ((inputBuffer = getchar()) != '\n' && inputBuffer != EOF) {};
                    printf("Invalid input: Expected an integer.\n");
                    continue;
                }

                if (FStack_push(stack, element))
                {
                    printf("Successfully added element [%i] to stack.\n", element);
                    break;
                }
                printf("Failed to push element to stack. Stack is full or cannot not found.\n");
                break;
            }
            break;

        // pop
        case 6:
            int poppedElement = FStack_pop(stack);

            if (poppedElement == STACK_ERROR)
            {
                printf("Failed to pop an element from stack. Stack is empty or cannot be found.\n");
                break;
            }
            printf("Popped element: %i\n", poppedElement);
            break;

        // peek
        case 7:
            int peekedElement = FStack_peek(stack);

            if (peekedElement == STACK_ERROR)
            {
                printf("Failed to peek an element from stack. Stack is empty or cannot be found.\n");
                break;
            }
            printf("Peeked element: %i\n", peekedElement);
            break;

        // search
        case 8:
            int search;

            while (true)
            {
                printf("Enter element you wish to search.\n> ");
                if (scanf("%i", &search) != 1)
                {
                    int inputBuffer;
                    while ((inputBuffer = getchar()) != '\n' && inputBuffer != EOF) {};
                    printf("Invalid input: Expected an integer.\n");
                    continue;
                }

                printf("Element [%i] was found at index [%i].\n", search, FStack_search(stack, search));
                break;
            }
            break;

        default:
            printf("Command not found.\n");
        }
    }
}
*/
