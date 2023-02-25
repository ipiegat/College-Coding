from CircularQueue import CircularQueue


class Test_CircularQueue_Methods:
    def test_len():
        queue = CircularQueue()

        assert len(queue) == 0
        queue.enqueue(1)
        assert len(queue) == 1
        queue.enqueue(2)
        assert len(queue) == 2
        queue.enqueue(3)
        assert len(queue) == 3

    def test_enqueue():
        queue = CircularQueue()

        queue.enqueue(4)
        assert queue.first() == 4
        assert len(queue) == 1
        queue.enqueue(5)
        assert queue.first() == 4
        assert len(queue) == 2

    def test_dequeue():
        queue = CircularQueue()

        queue.enqueue(1)
        queue.enqueue(2)
        assert len(queue) == 2

        result1 = queue.dequeue()
        assert result1 == 1
        assert len(queue) == 1

        result2 = queue.dequeue()
        assert result2 == 2
        assert queue.is_empty() == True


if __name__ == "__main__":
    Test_CircularQueue_Methods.test_len()
    Test_CircularQueue_Methods.test_enqueue()
    Test_CircularQueue_Methods.test_dequeue()

