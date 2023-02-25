class CircularQueue:
    DEFAULT_CAPACITY = 10

    def __init__(self):
        """Creating an empty queue."""
        self._data = [None] * self.DEFAULT_CAPACITY
        self._front: int = 0
        self._back: int = 0
        self._size: int = 0

    def __len__(self):
        return self._size

    def is_empty(self):
        return len(self) == 0

    def first(self):
        """Return (but do not remove) the first element of the queue."""
        return self._data[self._front]

    def dequeue(self):
        "Remove and return the first element of the queue. (FIFO)"
        if self.is_empty():
            raise IndexError

        front = self._data[self._front]
        self._front += 1
        if self._front == self.DEFAULT_CAPACITY:
            self._front = 0
        self._size -= 1

        return front

    def enqueue(self, element):
        if len(self) == self.DEFAULT_CAPACITY:
            raise IndexError

        self._data[self._back] = element
        self._back += 1
        if self._back == self.DEFAULT_CAPACITY:
            self._back = 0

        self._size += 1
