/**
 * Exception thrown when attempting to push an element onto a full stack.
 */
class StackOverflowException extends Exception {
    public StackOverflowException(String message) {
        super(message);
    }
}

/**
 * Exception thrown when attempting to pop an element from an empty stack.
 */
class StackUnderflowException extends Exception {
    public StackUnderflowException(String message) {
        super(message);
    }
}

/**
 * A generic fixed-size stack implementation.
 * 
 * @param <T> the type of elements held in this stack
 */
public class FixedStack<T> {
    private T[] stack; // Array to hold the stack elements
    private int top;    // Index of the top element in the stack
    private int size;   // Maximum size of the stack

    /**
     * Constructs a FixedStack with a specified size.
     * 
     * @param size the maximum number of elements the stack can hold
     */
    @SuppressWarnings("unchecked")
    public FixedStack(int size) {
        this.stack = (T[]) new Object[size]; // Create a generic array
        this.size = size; // Set the maximum size
        this.top = -1;    // Initialize the top index to -1 (indicating an empty stack)
    }

    /**
     * Returns the maximum size of the stack.
     * 
     * @return the size of the stack
     */
    public int getSize() {
        return this.size; // Return the size of the stack
    }

    /**
     * Displays the current elements in the stack.
     * If the stack is empty, it outputs "{}".
     */
    public void display() {
        // Check if the stack is empty
        if (this.isEmpty()) {
            System.out.println("{}"); // Output empty stack representation
            return;
        }

        StringBuilder out = new StringBuilder("{");
        // Iterate through the stack and append elements to the output
        for (int i = 0; i <= top; ++i) {
            out.append(stack[i]); // Append current element
            if (i < top) out.append(", "); // Append a comma if not the last element
        }
        out.append("}");
        System.out.println(out.toString()); // Print the stack contents
    }

    /**
     * Pushes an element onto the top of the stack.
     * 
     * @param element the element to be pushed onto the stack
     * @throws StackOverflowException if the stack is full
     */
    public void push(T element) throws StackOverflowException {
        // Check if the stack is full
        if (top == size - 1) throw new StackOverflowException("Stack is full. Cannot push element.");
        stack[++top] = element; // Increment the top index and add the element
    }

    /**
     * Pops the top element from the stack.
     * 
     * @return the top element from the stack
     * @throws StackUnderflowException if the stack is empty
     */
    public T pop() throws StackUnderflowException {
        // Check if the stack is empty
        if (this.isEmpty()) throw new StackUnderflowException("Stack is empty. Cannot pop element.");
        return stack[top--]; // Return the top element and decrement the top index
    }

    /**
     * Peeks at the top element of the stack without removing it.
     * 
     * @return the top element of the stack
     * @throws StackUnderflowException if the stack is empty
     */
    public T peek() throws StackUnderflowException {
        // Check if the stack is empty
        if (this.isEmpty()) throw new StackUnderflowException("Stack is empty. Cannot peek.");
        return stack[top]; // Return the top element without removing it
    }

    /**
     * Checks if the stack is empty.
     * 
     * @return true if the stack is empty, false otherwise
     */
    public boolean isEmpty() {
        return top == -1; // Returns true if top index is -1 (empty stack)
    }

    /**
     * Performs a linear search for an element in the stack.
     * 
     * @param element the element to search for
     * @return the index of the element if found, -1 otherwise
     */
    public int linearSearch(T element) {
        // Iterate through the stack to find the element
        for (int i = 0; i <= this.top; ++i) {
            // Check for equality (note: this will check for reference equality for objects)
            if (element == stack[i]) return i; // Return index if found
        }
        return -1; // Return -1 if the element is not found
    }
}
