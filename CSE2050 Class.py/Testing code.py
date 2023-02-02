def duplicates_1(L):
    n = len(L)
    for i in range(n):
        for j in range(i, n):
            if L[i] == L[j]:
                return True
    
    return False

import time

# from duplicates import duplicates_1

n = 1000000
for i in range(5):
    start_time = time.time()
    duplicates_1(list(range(n)))
    end_time = time.time()
    timetaken = end_time - start_time

    print("Time taken for n = ", n, ":", timetaken)


    