import time
import numpy as np

def problem1():
    
    # part 1
    value = 1254632
    times1 = []
    x = 0

    for _ in range(3):
        ctr = 0
        x += 10
        start = time.time()
        for _ in range(2**x):
            ctr += 1
            _ = ctr & value
        
        end = time.time()
        total = end - start
        times1.append(f"Time for 2^{x}: {total} seconds")
    
    # part 2
    times2 = []
    x = 0
    value = 3456

    for _ in range(3):
        ctr = 0
        x += 10
        start = time.time()
        for _ in range(2**x):
            ctr += 1
            _ = (ctr ^ 990) + (ctr/value)
        
        end = time.time()
        total = end - start
        times2.append(f"Time for 2^{x}: {total} seconds")
    
    return f"Part 1: {times1}\nPart 2: {times2}"

def estimation(answers1, answers2):

    exponents = [10, 20, 30]
    coefficients1 = np.polyfit(exponents, answers1, 2)
    coefficients2 = np.polyfit(exponents, answers2, 2)

    function1 = np.poly1d(coefficients1)
    function2 = np.poly1d(coefficients2)

    estimated_time1 = function1(480)
    estimated_time2 = function2(480)

    return f"Estimated time for Part 1 (2^480): {estimated_time1} seconds\nEstimated time for Part 2 (2^480): {estimated_time2} seconds"

if __name__ == "__main__":
    answers = problem1()
    # results below
    """
    Part 1: ['Time for 2^10: 0.0 seconds', 'Time for 2^20: 0.07856202125549316 seconds', 
    'Time for 2^30: 82.6774411201477 seconds']
    
    Part 2: ['Time for 2^10: 0.0 seconds', 'Time for 2^20: 0.13591599464416504 seconds', 
    'Time for 2^30: 139.3803141117096 seconds']
    """

    answers1 = [0.0, 0.07856202125549316, 82.6774411201477]
    answers2 = [0.0, 0.13591599464416504, 139.3803141117096]

    print(estimation(answers1, answers2))
    # result below
    """
    Estimated time for Part 1 (2^480): 89208.15517592432 seconds
    Estimated time for Part 2 (2^480): 150382.65722608566 seconds
    """
