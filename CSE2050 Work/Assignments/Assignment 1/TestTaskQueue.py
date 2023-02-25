import unittest
from TaskQueue import Task, TaskQueue


class TestTaskMethods(unittest.TestCase):
    def test_constructor(self):
        task = Task(id=5, time_left=10)
        self.assertEqual(task.id, 5)
        self.assertEqual(task.time_left, 10)

    def test_reduce_time(self):
        task = Task(id=5, time_left=10)
        task.reduce_time(4)
        self.assertEqual(task.time_left, 6)


class TestTaskQueueMethods(unittest.TestCase):
    def test_constructor(self):
        task_queue = TaskQueue(time_per_task=3)
        self.assertEqual(task_queue.time_per_task, 3)
        self.assertEqual(task_queue.current, None)
        self.assertEqual(task_queue.last, None)

    def test_len(self):
        task1 = Task(id=1, time_left=1)
        task2 = Task(id=2, time_left=2)
        task3 = Task(id=3, time_left=3)
        task_queue = TaskQueue(time_per_task=3)
        self.assertEqual(task_queue.__len__(), 0)
        task_queue.add_task(task1)
        self.assertEqual(task_queue.__len__(), 1)
        task_queue.add_task(task2)
        self.assertEqual(task_queue.__len__(), 2)
        task_queue.add_task(task3)
        self.assertEqual(task_queue.__len__(), 3)

    def test_is_empty(self):
        task1 = Task(id=1, time_left=1)
        task2 = Task(id=2, time_left=2)
        task3 = Task(id=3, time_left=3)
        task_queue = TaskQueue(time_per_task=3)
        self.assertTrue(task_queue.is_empty())
        task_queue.add_task(task1)
        task_queue.add_task(task2)
        task_queue.add_task(task3)
        self.assertFalse(task_queue.is_empty())

    def test_add_task(self):
        task1 = Task(id=1, time_left=1)
        task2 = Task(id=2, time_left=2)
        task3 = Task(id=3, time_left=3)
        task_queue = TaskQueue(time_per_task=3)
        task_queue.add_task(task1)
        task_queue.add_task(task2)
        task_queue.add_task(task3)
        self.assertEqual(task_queue.current, task1)
        self.assertEqual(task_queue.current.next, task2)
        self.assertEqual(task_queue.current.next.next, task3)
        self.assertEqual(task_queue.current.next.next.next, task1)

    def test_execute_tasks(self):
        task1 = Task(id=1, time_left=1)
        task2 = Task(id=2, time_left=2)
        task3 = Task(id=3, time_left=3)
        task_queue = TaskQueue(time_per_task=2)
        task_queue.add_task(task1)
        task_queue.add_task(task2)
        task_queue.add_task(task3)

        total_time = task_queue.execute_tasks()

        self.assertEqual(task1.time_left, 0)
        self.assertEqual(task2.time_left, 0)
        self.assertEqual(task3.time_left, 0)
        self.assertEqual(total_time, 6)

    def test_remove_tasks(self):
        task1 = Task(id=1, time_left=1)
        task2 = Task(id=2, time_left=2)
        task3 = Task(id=3, time_left=3)
        task_queue = TaskQueue(time_per_task=2)
        task_queue.add_task(task1)
        task_queue.add_task(task2)
        task_queue.add_task(task3)

        task_queue.remove_task(1)
        self.assertEqual(task_queue.__len__(), 2)
        self.assertEqual(task_queue.current, task2)
        task_queue.remove_task(2)
        self.assertEqual(task_queue.__len__(), 1)
        self.assertEqual(task_queue.current, task3)
        task_queue.remove_task(3)
        self.assertEqual(task_queue.__len__(), 0)
        self.assertEqual(task_queue.current, None)


if __name__ == "__main__":
    # unittest.main()

    t1 = Task(id=1, time_left=3)
    t2 = Task(id=2, time_left=1)
    t3 = Task(id=3, time_left=5)
    tasks = [t1, t2, t3]

    TQ = TaskQueue(time_per_task=1)

    for task in tasks:
        TQ.add_task(task)  # info truncated to not give away the answer

    time = TQ.execute_tasks()  # note that this prints info *and* returns a
    print(f"time = {time}")
