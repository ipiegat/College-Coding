import random
import time

def quicksort(arr, pivot_strategy='last'):
    def partition(low, high):
        if pivot_strategy == 'random':
            pivot_index = random.randint(low, high)
            arr[pivot_index], arr[high] = arr[high], arr[pivot_index]
        pivot = arr[high]
        i = low - 1
        for j in range(low, high):
            if arr[j] < pivot:
                i += 1
                arr[i], arr[j] = arr[j], arr[i]
        arr[i+1], arr[high] = arr[high], arr[i+1]
        return i + 1
    
    def quicksort_recursive(low, high):
        if low < high:
            pi = partition(low, high)
            quicksort_recursive(low, pi-1)
            quicksort_recursive(pi+1, high)
    
    quicksort_recursive(0, len(arr) - 1)
    return arr


if __name__ == "__main__":

    # arrays to be sorted using last element as pivot
    arr_100_last = [random.randint(1, 10000) for _ in range(100)]
    arr_500_last = [random.randint(1, 10000) for _ in range(500)]
    arr_1000_last = [random.randint(1, 10000) for _ in range(1000)]
    arr_1500_last = [random.randint(1, 10000) for _ in range(1500)]
    arr_2000_last = [random.randint(1, 10000) for _ in range(2000)]
    arr_last = [arr_100_last, arr_500_last, arr_1000_last, arr_1500_last, arr_2000_last]

    # arrays to be sorted using random pivot
    arr_100_random = [random.randint(1, 10000) for _ in range(100)]
    arr_500_random = [random.randint(1, 10000) for _ in range(500)]
    arr_1000_random = [random.randint(1, 10000) for _ in range(1000)]
    arr_1500_random = [random.randint(1, 10000) for _ in range(1500)]
    arr_2000_random = [random.randint(1, 10000) for _ in range(2000)]
    arr_random = [arr_100_random, arr_500_random, arr_1000_random, arr_1500_random, arr_2000_random]

    print("\nUsing the last element as pivot:\n")
    for arr in arr_last:
        start = time.time()
        quicksort(arr, 'last')
        end = time.time() - start
        print(f'Array completed in {end} seconds.\n')

    print("\nUsing a random element as pivot:\n")
    for arr in arr_random:
        start = time.time()
        quicksort(arr, 'random')
        end = time.time() - start
        print(f'Array completed in {end} seconds.\n')
