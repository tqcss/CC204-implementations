
class StackOverflowException(Exception):
    """Exception raised when attempting to push onto a full stack."""
    def __init__(self, message: str):
        super().__init__(message)


class StackUnderflowException(Exception):
    """Exception raised when attempting to pop from an empty stack."""
    def __init__(self, message: str):
        super().__init__(message)


class FixedStack:
    """A generic fixed-size stack implementation.

    Attributes:
        stack (list): The list to hold the stack elements.
        size (int): The maximum size of the stack.
    """
    
    def __init__(self, size: int):
        """Initializes the FixedStack with a specified size.

        Args:
            size (int): The maximum number of elements the stack can hold.
        """
        self.stack = []  # List to hold stack elements
        self.size = size  # Maximum size of the stack

    def display(self) -> None:
        """Displays the current elements in the stack."""
        print(self.stack)  # Print the elements in the stack

    def push(self, element: any) -> None:
        """Pushes an element onto the top of the stack.

        Args:
            element (any): The element to be pushed onto the stack.

        Raises:
            StackOverflowException: If the stack is full.
        """
        if len(self.stack) == self.size:
            raise StackOverflowException('Stack is full. Cannot push element.')
        self.stack.append(element)  # Append the element to the stack

    def pop(self) -> any:
        """Pops the top element from the stack.

        Returns:
            any: The top element from the stack.

        Raises:
            StackUnderflowException: If the stack is empty.
        """
        if self.is_empty():
            raise StackUnderflowException('Stack is empty. Cannot pop element.')
        return self.stack.pop()  # Remove and return the top element

    def peek(self) -> any:
        """Returns the top element of the stack without removing it.

        Returns:
            any: The top element of the stack.

        Raises:
            StackUnderflowException: If the stack is empty.
        """
        if self.is_empty():
            return None  # Return None if stack is empty
        return self.stack[-1]  # Return the top element without removing it

    def is_empty(self) -> bool:
        """Checks if the stack is empty.

        Returns:
            bool: True if the stack is empty, False otherwise.
        """
        return len(self.stack) == 0  # Returns true if stack has no elements

    def search(self, element: any) -> int:
        """Searches for an element in the stack.

        Args:
            element (any): The element to search for.

        Returns:
            int: The index of the element if found, -1 otherwise.
        """
        try:
            return self.stack.index(element)  # Find the index of the element
        except ValueError:
            return -1  # Return -1 if the element is not found
