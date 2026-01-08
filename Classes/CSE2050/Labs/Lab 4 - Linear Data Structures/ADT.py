from typing import Optional


class _Node:
    """Node class to create
    individual linked list nodes"""

    def __init__(self, element, next):
        self._element = element
        self._next: Optional[_Node] = next


class Stack_L:  # LIFO
    def __init__(self):
        self._L = list()  # Composition: the Stack_L class has a List

    def push(self, item):
        self._L.append(item)

    def pop(self):
        """Remove and returns the element at the top of stack"""
        if self.isempty() == False:
            return self._L.pop()
        else:
            raise IndexError  # Raises error when trying to pop from the empty stack

    def peek(self):
        if self.isempty() == False:
            return self._L[-1]
        else:
            raise IndexError  # Raises error when trying to pop from the empty stack

    def __len__(self):
        return len(self._L)

    def isempty(self):
        if self.__len__() == 0:
            return True

        return False


class Queue_L:  # FIFO
    def __init__(self):
        self._L = []

    def enqueue(self, item):
        return self._L.append(item)

    def dequeue(self):
        if self.__len__() > 0:
            return self._L.pop(0)
        else:
            raise IndexError  # Raises error when trying to deque from the empty queue

    def peek(self):
        return self._L[0]

    def __len__(self):
        return len(self._L)

    def isempty(self):
        if self.__len__() == 0:
            return True

        return False


class Stack_LL:  # FIFO
    def __init__(self):
        self._head: Optional[_Node] = None
        self._size: int = 0

    def __len__(self):
        """Returns the size of the stack"""
        return self._size

    def is_empty(self):
        """Returns True if the stack is empty"""
        return len(self) == 0

    def push(self, element):
        """Add "element" to the top of the stack"""
        self._head = _Node(element, self._head)
        self._size += 1

    def pop(self):
        """Remove element from the top of the stack"""
        # make sure we have an element to give
        if self.is_empty():
            raise IndexError

        old_head = self._head
        self._head = self._head._next
        self._size -= 1
        return old_head._element

    def top(self):
        """Only read the element and do not remove it."""
        if self.is_empty():
            raise IndexError

        return self._head._element


class Queue_LL:
    def __init__(self):
        self._head: Optional[_Node] = None
        self._tail: Optional[_Node] = None
        self._size: int = 0

    def __len__(self):
        """Returns the size of the queue"""
        return self._size

    def is_empty(self):
        """Returns True if the queue is empty"""
        return len(self) == 0

    def first(self):
        """Returns (but do not remove) the first element in the queue"""
        return self._head._element

    def enqueue(self, element):
        """Add "element" to the back of the queue"""
        if self.is_empty():
            self._head = _Node(element, None)
            self._tail = self._head
        else:
            self._tail._next = _Node(element, None)
            self._tail = self._tail._next

        self._size += 1

    def dequeue(self):
        """Remove element from the front of the queue"""
        if self.is_empty():
            raise IndexError

        old_head = self._head
        self._head = self._head._next
        self._size -= 1

        if self._head is None:
            self._tail = None

        return old_head._element
