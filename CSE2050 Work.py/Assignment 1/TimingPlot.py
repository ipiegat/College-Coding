import random
import time
from Fitting import *
from tqdm import tqdm


def bubble_sort(L):
    start_time = time.time()
    n = len(L)  # no. of items in list
    for i in range(n):  # for every item
        for j in range(n):  # compare to every other item
            if L[i] < L[j]:  # if out of order:
                L[i], L[j] = L[j], L[i]  # swap items
    end_time = time.time()
    total_time = end_time - start_time

    return total_time, L


def get_data(max_n):
    x = []
    y = []

    for n in tqdm(range(1, max_n)):
        x.append(n)
        L = [random.randint(0, n) for i in range(n)]
        t, L = bubble_sort(L)
        y.append(t)

    return x, y


if __name__ == "__main__":
    x, y = get_data(1000)
    quad_line = best_fit(quad, x, y)
    lin_line = best_fit(lin, x, y)

    create_fig(quad_line, lin_line, x, y)
