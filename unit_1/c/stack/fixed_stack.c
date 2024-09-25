// CODE IMPLEMENTATION FOR A FIXED-SIZE STACK
// This implementation provides basic operations (push, pop, peek, search, and print) 
// for a stack with a fixed maximum size. The stack uses a dynamic array to store elements 
// and keeps track of the current top of the stack using an index.

// Necessary libraries for I/O operations, dynamic memory allocation, and type definitions.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define STACK_ERROR INT_MIN // Define a constant value for error handling (returned when stack operations fail).

// STRUCTURE DEFINITION

// FStack: A structure representing a fixed-size stack.
// - topIndex: Index of the top element (starts from -1 to indicate an empty stack).
// - size: The maximum number of elements the stack can hold.
// - bottom: A dynamically allocated array to store stack elements.
typedef struct FStack {
    int topIndex; // Tracks the index of the last element pushed onto the stack.
    int size;     // Maximum size (capacity) of the stack.
    int *bottom;  // Pointer to the array that holds the stack's elements.
} FStack;

// FUNCTION DECLARATIONS

// Instantiates and allocates memory for a stack of a given fixed size.
// Returns a pointer to the newly created stack. If memory allocation fails, returns NULL.
FStack *FStack_create(const int size);

// Deallocates memory used by the stack and its elements.
// Takes the stack pointer (FStack *) to allow proper nullification.
// Returns true if the operation was successful, false otherwise.
bool FStack_delete(FStack *stack);

// Pushes an integer value onto the stack.
// Returns true if the operation was successful, false if the stack is full or invalid.
bool FStack_push(FStack *stack, const int value);

// Removes and returns the top element of the stack.
// Returns STACK_ERROR if the stack is empty or invalid.
int FStack_pop(FStack *stack);

// Checks if the stack is empty.
// Returns true if the stack contains no elements, false otherwise.
bool FStack_isEmpty(FStack *stack);

// Returns the top element of the stack without modifying it.
// Returns STACK_ERROR if the stack is empty.
int FStack_peek(FStack *stack);

// Searches for a specific value in the stack and returns its index.
// The index is zero-based, starting from the bottom of the stack.
// Returns -1 if the value is not found in the stack.
int FStack_linearSearch(FStack *stack, const int value);

// Prints the contents of the stack in a human-readable format.
// Stack elements are enclosed in square brackets, separated by commas.
// Returns true if successful, false if the stack is NULL.
bool FStack_print(FStack *stack);


// FUNCTION DEFINITIONS

// Instantiates a stack with the specified size, allocates memory for the structure, and initializes members.
FStack *FStack_create(const int size) {
    FStack *stack = (FStack *)malloc(sizeof(FStack));
    if (!stack)
        return NULL;  // Return NULL if memory allocation fails.

    stack->size = size;
    stack->topIndex = -1;  // The stack is initially empty, so the topIndex is -1.
    stack->bottom = (int *)malloc(size * sizeof(int)); // Allocate memory for the stack's elements.

    if (stack->bottom == NULL) {
        free(stack);  // If element array allocation fails, free the stack structure.
        return NULL;
    }
    return stack;
}

// Frees the memory allocated for the stack's elements and the stack itself.
// Takes a stack pointer (FStack *) to allow setting the stack pointer to NULL after deallocation.
bool FStack_delete(FStack *stack) {
    if (!stack) return false; // Return false if the stack is already NULL.
    
    free((stack)->bottom); // Free the memory allocated for the stack's elements.
    free(stack);           // Free the stack structure itself.
    stack = NULL;          // Set the stack pointer to NULL to avoid dangling pointers.
    
    return true;
}

// Pushes a new element onto the stack.
// If the stack is full (i.e., topIndex reaches the size limit), it returns false.
// Otherwise, the element is added, and the topIndex is incremented.
bool FStack_push(FStack *stack, const int value) {
    if (!stack || stack->topIndex == stack->size - 1)  // Check if the stack is full or invalid.
        return false;
    
    stack->bottom[++stack->topIndex] = value;  // Increment topIndex and add the value.
    return true;
}

// Removes and returns the top element from the stack.
// If the stack is empty or NULL, it returns STACK_ERROR.
int FStack_pop(FStack *stack) {
    if (!stack || FStack_isEmpty(stack))  // Check if the stack is empty or NULL.
        return STACK_ERROR;
    
    return stack->bottom[stack->topIndex--];  // Return the top element and decrement the topIndex.
}

// Returns true if the stack is empty (i.e., topIndex is -1).
bool FStack_isEmpty(FStack *stack) {
    return (!stack || stack->topIndex == -1);  // Stack is empty if topIndex is -1 or stack is NULL.
}

// Returns the element at the top of the stack without modifying it.
// Returns STACK_ERROR if the stack is empty.
int FStack_peek(FStack *stack) {
    if (FStack_isEmpty(stack))
        return STACK_ERROR;
    
    return stack->bottom[stack->topIndex];  // Return the element at the top of the stack.
}

// Searches for a specific value within the stack.
// Iterates through the stack and returns the index of the value if found.
// If the value is not found, returns -1.
int FStack_linearSearch(FStack *stack, const int value) {
    for (int index = 0; index <= stack->topIndex; ++index) {
        if (stack->bottom[index] == value)
            return index;  // Return the index of the found value.
    }
    return -1;  // Return -1 if the value is not found.
}

// Prints the stack's contents in a readable format.
// Outputs elements in the form [a, b, c].
// Returns false if the stack is NULL.
bool FStack_print(FStack *stack) {
    if (!stack) return false; // Return false if the stack is NULL.

    if (FStack_isEmpty(stack)) {
        printf("[]\n");  // Print an empty array if the stack has no elements.
        return true;
    }

    // Print each element in the stack, separated by commas.
    printf("[");
    for (int i = 0; i < stack->topIndex; ++i) {
        printf("%i, ", stack->bottom[i]);
    }
    printf("%i]\n", stack->bottom[stack->topIndex]);  // Print the last element without a trailing comma.
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

                printf("Element [%i] was found at index [%i].\n", search, FStack_linearSearch(stack, search));
                break;
            }
            break;

        default:
            printf("Command not found.\n");
        }
    }
}
*/
