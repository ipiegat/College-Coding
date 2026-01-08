import unittest
from ADT import _Node, Stack_LL, Stack_L, Queue_LL, Queue_L


class Test_Node_Methods(unittest.TestCase):
    def test_constructor(self):
        node1 = _Node(element=1, next=None)
        node2 = _Node(element=2, next=node1)
        self.assertEqual(node1._element, 1)
        self.assertEqual(node2._element, 2)
        self.assertEqual(node2._next._element, 1)


class Test_Stack_L_Methods(unittest.TestCase):
    def test_len(self):
        stack = Stack_L()

        self.assertEqual(len(stack), 0)
        stack.push(1)
        self.assertEqual(len(stack), 1)
        stack.push(2)
        self.assertEqual(len(stack), 2)
        stack.push(3)
        self.assertEqual(len(stack), 3)

    def test_push(self):
        stack = Stack_L()

        stack.push(4)
        self.assertEqual(stack.peek(), 4)
        self.assertEqual(len(stack), 1)
        stack.push(5)
        self.assertEqual(stack.peek(), 5)
        self.assertEqual(len(stack), 2)

    def test_pop(self):
        stack = Stack_L()

        stack.push(1)
        stack.push(2)
        self.assertEqual(len(stack), 2)

        result2 = stack.pop()
        self.assertEqual(result2, 2)
        self.assertEqual(len(stack), 1)

        result1 = stack.pop()
        self.assertEqual(result1, 1)
        self.assertTrue(stack.isempty())


class Test_Queue_L_Methods(unittest.TestCase):
    def test_len(self):
        queue = Queue_L()

        self.assertEqual(len(queue), 0)
        queue.enqueue(1)
        self.assertEqual(len(queue), 1)
        queue.enqueue(2)
        self.assertEqual(len(queue), 2)
        queue.enqueue(3)
        self.assertEqual(len(queue), 3)

    def test_enqueue(self):
        queue = Queue_L()

        queue.enqueue(4)
        self.assertEqual(queue.peek(), 4)
        self.assertEqual(len(queue), 1)
        queue.enqueue(5)
        self.assertEqual(queue.peek(), 4)
        self.assertEqual(len(queue), 2)

    def test_dequeue(self):
        queue = Queue_L()

        queue.enqueue(1)
        queue.enqueue(2)
        self.assertEqual(len(queue), 2)

        result1 = queue.dequeue()
        self.assertEqual(result1, 1)
        self.assertEqual(len(queue), 1)

        result2 = queue.dequeue()
        self.assertEqual(result2, 2)
        self.assertTrue(queue.isempty())


class Test_Stack_LL_Methods(unittest.TestCase):
    def test_len(self):
        stack = Stack_LL()

        self.assertEqual(len(stack), 0)
        stack.push(1)
        self.assertEqual(len(stack), 1)
        stack.push(2)
        self.assertEqual(len(stack), 2)
        stack.push(3)
        self.assertEqual(len(stack), 3)

    def test_push(self):
        stack = Stack_LL()

        stack.push(4)
        self.assertEqual(stack.top(), 4)
        self.assertEqual(len(stack), 1)
        stack.push(5)
        self.assertEqual(stack.top(), 5)
        self.assertEqual(len(stack), 2)

    def test_pop(self):
        stack = Stack_LL()

        stack.push(1)
        stack.push(2)
        self.assertEqual(len(stack), 2)

        result2 = stack.pop()
        self.assertEqual(result2, 2)
        self.assertEqual(len(stack), 1)

        result1 = stack.pop()
        self.assertEqual(result1, 1)
        self.assertTrue(stack.is_empty())


class Test_Queue_LL_Methods(unittest.TestCase):
    def test_len(self):
        queue = Queue_LL()

        self.assertEqual(len(queue), 0)
        queue.enqueue(1)
        self.assertEqual(len(queue), 1)
        queue.enqueue(2)
        self.assertEqual(len(queue), 2)
        queue.enqueue(3)
        self.assertEqual(len(queue), 3)

    def test_enqueue(self):
        queue = Queue_LL()

        queue.enqueue(4)
        self.assertEqual(queue.first(), 4)
        self.assertEqual(len(queue), 1)
        queue.enqueue(5)
        self.assertEqual(queue.first(), 4)
        self.assertEqual(len(queue), 2)

    def test_dequeue(self):
        queue = Queue_LL()

        queue.enqueue(1)
        queue.enqueue(2)
        self.assertEqual(len(queue), 2)

        result1 = queue.dequeue()
        self.assertEqual(result1, 1)
        self.assertEqual(len(queue), 1)

        result2 = queue.dequeue()
        self.assertEqual(result2, 2)
        self.assertTrue(queue.is_empty())


if __name__ == "__main__":
    unittest.main()
