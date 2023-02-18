from TaskQueue import *

t1 = Task(id=1, time_left=3)
t2 = Task(id=2, time_left=1)
t3 = Task(id=3, time_left=5)
tasks = [t1, t2, t3]

TQ = TaskQueue(time_per_task=1)

for task in tasks:
    TQ.add_task(task) # info truncated to not give away the answer

time = TQ.execute_tasks() # note that this prints info *and* returns a
print(f"time = {time}")