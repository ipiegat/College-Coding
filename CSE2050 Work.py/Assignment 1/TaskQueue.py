class Task():
    def __init__(self, id: int, time_left: float):
        self.id = id
        self.time_left = time_left
        self.next = None
    
    def reduce_time(self, amount):
        self.time_left = max(0, self.time_left - amount)
    
class TaskQueue():
    def __init__(self, current, time_per_task = 1):
        self.current = current
        self.last = current
        self.time_per_task = time_per_task

    def add_task(self, new_task):
        if self.is_empty() == True: # if the list is empty,
            self.current = new_task # set the head to the new task
            self.last = new_task # set the tail to the new task
            new_task.next = self.current # point it towards itself
        
        if self.is_empty() == False: # if list is not empty and I want to add task before head
            new_task.next = self.current # point new task to the current head
            self.current = new_task # set the head to the new task
            self.last.next = self.current # point the last node to the head

    def remove_task(self, id: int):
        if self.is_empty() == False: # if the list is not empty
            if self.current.id == id: # if the head's ID is the ID we are looking for
                self.current = self.current.next # place the next node as the head
    
            else:
                cur = self.current # create placement variable
                while cur.next.id != id: # check the list until the ID we are looking for is found
                    cur = cur.next # if ID does not match, move to the next node
                    if cur == self.current: # when the next node points to the head we know we went through everything
                        raise RuntimeError(f"Task is not found for id {id}") # thus the ID can't be in the list
        else: # if the list is empty
            raise RuntimeError(f"Task is not found for id {id}") # raise error immediately
    
    def len(self):
        count = 0 # initialize the count
        cur = self.current # create placement variable
        while cur != self.current: # while the node doesn't point to the head
            count += 1 # add one to the count
            cur = cur.next # set cur to the next node in the list then repeat until loop breaks
        
        return count

    def is_empty(self):
        if self.len == 0: # if the length of the list is 0 
            return True # return True (is is empty)
        else: # if length is not 0
            return False # return False (it is not empty)

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

        

