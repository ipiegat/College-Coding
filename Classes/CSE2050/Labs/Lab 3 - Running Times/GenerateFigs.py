from matplotlib import pyplot as plt  # import plotting funcs
import numpy as np
from tqdm import tqdm
from TimeFunctions import time_function  # import the time function you will write
from Duplicates import (
    has_duplicates_2,
    has_duplicates_1,
)  # import the has_duplicates functions you are interested in


# All code below is included as a demo. Feel free to change any of it.

##### Initialize datasets
# Pick 3 x-values
x = np.arange(1, 5000, 100)

##### Measure the running times
# Generate 3 corresponding y-values
y1 = []
for n in tqdm(x):
    L = [i for i in range(n)]  # Worst case: A list with no duplicates
    y1.append(time_function(has_duplicates_1, L))  # append running time to y

y2 = []
for n in tqdm(x):
    L2 = [i for i in range(n)]  # Worst case: A list with no duplicates
    y2.append(time_function(has_duplicates_2, L2))  # append running time to y

y1 = np.array(y1)
y2 = np.array(y2)


##### Plot datasets
plt.figure()  # create a new figure
plt.scatter(
    x, np.log(y1), c="r", marker="x", label="has_duplicates_1"
)  # add scatter plot to figure
plt.scatter(
    x, np.log(y2), c="b", marker="o", label="has_duplicates_2"
)  # add scatter plot to figure
plt.ylabel("running time (s)")  # label y axis
plt.legend()  # add legend to figure
plt.show()  # show figure on local computer
# plt.savefig("dups")  # save figure

# Note: You can either use plt.show() or plt.savefig(). Using both does not work.
