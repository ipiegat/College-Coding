class Task:
    def __init__(self, id: int, time_left: float):
        self.id = id
        self.time_left = time_left
        self.next = None

    def reduce_time(self, amount: float) -> None:
        self.time_left = max(0, self.time_left - amount)


class TaskQueue:
    def __init__(self, current: Task, time_per_task: float = 1):
        """
        Params:

        * current - the current task in que
        * time_per_task - how much time spent on each task before going to next
        """
        self.current = current
        self.last = current
        self.time_per_task = time_per_task

    def add_task(self, new_task: Task):
        if self.is_empty():
            self.current = new_task
            self.last = new_task
        else:
            self.last.next = new_task
            self.last = new_task

    def remove_task(self, id: int):
        if self.is_empty():
            raise RuntimeError(f"Task is not found for id {id}")

        if self.current.id == id:
            self.current = self.current.next
    
        cur = self.current
        while cur.next.id != id:
            cur = cur.next
        
            if cur == None:
                raise RuntimeError(f"Task is not found for id {id}")
        
        cur.next = cur.next.next

    def queue_length(self):
        count = 0
        cur = self.current
        while cur != None:
            count += 1
            cur = cur.next

        return count

    def is_empty(self) -> bool:
        length = self.queue_length()
        if length == 0:
            return True
        else:
            return False

    def execute_tasks(self):
        total_time = 0  # initialize sum
        while not self.is_empty():  # while the queue is not empty
            top = self.current
            self.remove_task(top.id)  # top is the first element in the queue

            # if the time left to complete task is greater than the alloted time
            if top.time_left > self.time_per_task:

                # add the total alloted time to total time
                total_time += self.time_per_task

                # subtracts time used to complete task from time left
                top.reduce_time(self.time_per_task)

                # moves to back if the task isn't completed
                self.add_task(top)

            else:  # runs when total time to complete task is less than the alloted time

                # adds the time to complete task, not the total alloted time
                total_time += top.time_left
                print(f"Task with ID {top.id} is done")

        return total_time  # return total amount of time we worked

