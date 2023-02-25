from typing import Optional

class Node:
    def __init__(self, element, next):
        self._element = element
        self._next: Optional[Node] = next

class CircularQueue:
    DEFAULT_CAPACITY = 10

    def __init__(self):
        """ Creating an empty queue. """
        self._data = [None] * self.DEFAULT_CAPACITY
        self._front: Optional[Node] = None
        self._back: Optional[Node] = None
        self._size: int = 0


    def __len__(self):
        return self._size

    def is_empty(self):
        return len(self) == 0

    def first(self):
        """ Return (but do not remove) the first element of the queue. """
        return self._front._element

    def dequeue(self):
        " Remove and return the first element of the queue. (FIFO)"
        if self.is_empty:
            raise IndexError
        
        # a -> b -> c -> a
        old_front = self._front
        self._front._next = self._front
        self._back._next = self._front
        self._size -= 1

        if self._front is None:
            self._back = None
        
        return old_front._element

    def enqueue(self, element):
        if self.is_empty():
            self._front = Node(element, None)
            self._back = self._front
            self._back._next = self._front
        else:
            self._back._next = Node(element, self._front)
            self._back = self._back._next

        self._size += 1
