import os
import time

def BruteForce(solutions, nums):
    for i in solutions:
        for j in nums:
            if j + j == i:
                return True
            for k in nums:
                if k + j == i:
                    return True
    
    return False
                
def BinarySearch(nums, target, start_index):
    left, right = start_index, len(nums) - 1
    while left <= right:
        mid = (left + right) // 2
        if nums[mid] == target:
            return True
        elif nums[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    return False 

def BinarySearchSum(nums, solutions):
    nums.sort()
    for target in solutions:
        for i in range(len(nums)):
            complement = target - nums[i]
            if complement != nums[i] and BinarySearch(nums, complement, i + 1):
                return True
    return False



if __name__ == "__main__":
    directory_path = "CSE3500\CollectionNumbers"

    file_pairs = {"listNumbers-10-nsol.txt": "listNumbers-10.txt",
             "listNumbers-100-nsol.txt": "listNumbers-100.txt",
             "listNumbers-1000-nsol.txt": "listNumbers-1000.txt",
             "listNumbers-10000-nsol.txt": "listNumbers-10000.txt",
             "listNumbers-100000-nsol.txt": "listNumbers-100000.txt",
             "listNumbers-1000000-nsol.txt": "listNumbers-1000000.txt"}

    for sol_file_name, num_file_name in file_pairs.items(): 
        sol_file_path = os.path.join(directory_path, sol_file_name)
        num_file_path = os.path.join(directory_path, num_file_name)
        solutions = []
        nums = []

        with open(sol_file_path, "r") as f:
            for line in f:
                solutions.append(int(line.strip()))
            
        with open(num_file_path, "r") as f:
            for line in f:
                nums.append(int(line.strip()))
                
        print(f"\nChecking file pair: {sol_file_name} and {num_file_name}")

        # Brute Force
        start = time.time()
        result = BruteForce(solutions, nums)
        elapsed_time = time.time() - start
        print(f"Brute Force Result: {result}")
        print(f"Brute Force Elapsed time: {elapsed_time} seconds")

        # Binary Search
        start = time.time()
        binary_search_result = BinarySearchSum(nums, solutions)
        binary_search_time = time.time() - start
        print(f"Binary Search Result: {binary_search_result}")
        print(f"Binary Search Elapsed Time: {binary_search_time} seconds")