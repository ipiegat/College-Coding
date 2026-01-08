import random
import time
from matplotlib import pyplot as plt
from Fitting import *
from tqdm import tqdm


def best_fit(func, xdata, ydata):
    """
    Write docstring here
    """
    # Find parameters for lin that best fit xdata and ydata
    params, _ = optimize.curve_fit(func, xdata, ydata)
    # unpack the calculated parameters
    # m = params[0]
    # b = params[1]
    # create an empty list for the line of best fit
    y_fit = []
    for x in xdata:
        y_fit.append(func(x, *params))

    return y_fit


def create_fig(y_fit_quad, y_fit_lin, xdata, ydata):
    # plot the raw data and the line of best fit
    plt.figure()
    plt.scatter(xdata, ydata)
    plt.plot(xdata, y_fit_quad, c="r", label="Quadratic")
    plt.plot(xdata, y_fit_lin, c="g", label="Linear")
    plt.xlabel("n")
    plt.ylabel("Duration (s)")
    plt.title("Best Fit")
    plt.legend()
    plt.show()
    #plt.savefig("bestfit")


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
