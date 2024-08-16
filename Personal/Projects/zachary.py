import random
import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np

def WriteToFile(int_count, start, end):

    with open(r"Personal\Projects\random_integers.txt", "w") as file:
        for _ in range(int_count):
            num = str(random.randint(start, end))
            file.write(num)
            file.write("\n")

    return int_count

def CountDuplicates():

    randint_array = []
    with open(r"Personal\Projects\random_integers.txt", "r") as file:
        for line in file:
            randint_array.append(int(line))
    
    duplicates_dict = {}
    for num in randint_array:
        count = randint_array.count(num)
        if num not in duplicates_dict:
            duplicates_dict[num] = count

    length = len(duplicates_dict)
    duplicates = num_ints - length
    return duplicates


if __name__ == "__main__":
    num_ints = 888
    WriteToFile(num_ints, 6, 1200)

    duplicates = CountDuplicates()
    print(duplicates)

# test


