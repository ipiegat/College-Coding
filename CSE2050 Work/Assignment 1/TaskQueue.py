class Task:
    def __init__(self, id: int, time_left: float):
        self.id = id
        self.time_left = time_left
        self.next = None

    def reduce_time(self, amount):
        self.time_left = max(0, self.time_left - amount)


class TaskQueue:
    def __init__(self, time_per_task=1):
        self.current = None
        self.last = None
        self.time_per_task = time_per_task

    def add_task(self, new_task):
        if self.is_empty():  # if the list is empty,
            self.current = new_task  # set the head to the new task
            self.last = new_task  # set the tail to the new task
            new_task.next = self.current  # point it towards itself

        else:  # if list is not empty and I want to add task before head
            new_task.next = self.current
            self.last.next = new_task
            self.last = new_task  # could be self.current = new_task

    def remove_task(self, id: int):
        if self.is_empty() == True:  # if the list is empty
            raise RuntimeError(f"Task with ID {id} was not found")  # raise error
        if self.is_empty() == False:  # if the list is not empty
            if self.len() == 1:  # if there is only one item in the list
                if self.current.id == id:  # and the item has the ID
                    self.current = None  # set the item to None
                else:  # if the one item does not have the ID
                    raise RuntimeError(
                        f"Task with ID {id} was not found"
                    )  # raise error
            if self.len() > 1:  # if there are two or more items in the list
                if self.current.id == id:  # if the head has the ID
                    self.current = self.current.next  # set the next item to be the head
                    self.last.next = self.current  # point the new item towards itself
                else:  # if the head does not have the ID
                    cur = self.current
                    while cur.id != id:  # while the ID isn't found
                        cur = cur.next  # move to the next in the list
                        if cur.next == self.current:
                            raise RuntimeError(f"Task with ID {id} was not found")

    def len(self):
        if self.current is None:
            return 0

        count = 1  # initialize the count
        cur = self.current  # create placement variable
        while cur.next != self.current:  # while the node doesn't point to the head
            count += 1  # add one to the count
            cur = (
                cur.next
            )  # set cur to the next node in the list then repeat until loop breaks

        return count

    def is_empty(self):
        if self.len() == 0:  # if the length of the list is 0
            return True  # return True (is is empty)
        else:  # if length is not 0
            return False  # return False (it is not empty)

    def execute_tasks(self):
        total_time = 0  # initialize sum
        while self.is_empty() == False:  # while the queue is not empty
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
                top.reduce_time(top.time_left)
                print(f"Task with ID {top.id} is done")

        return total_time  # return total amount of time we worked
