from matplotlib import pyplot as plt  # import plotting funcs
from TimeFunctions import time_function  # import the time function you will write
from Duplicates import (
    has_duplicates_2,
    has_duplicates_1,
)  # import the has_duplicates functions you are interested in


# All code below is included as a demo. Feel free to change any of it.

##### Initialize datasets
# Pick 3 x-values
x = [
    1,
    50,
    100,
    150,
    200,
    250,
    300,
    350,
    400,
    450,
    500,
    550,
    600,
    650,
    700,
    750,
    800,
    850,
    900,
    950,
    1000,
]


##### Measure the running times
# Generate 3 corresponding y-values
y1 = []
for n in x:
    L = [i for i in range(n)]  # Worst case: A list with no duplicates
    y1.append(time_function(has_duplicates_1, L))  # append running time to y

y2 = []
for n in x:
    L2 = [i for i in range(n)]  # Worst case: A list with no duplicates
    y2.append(time_function(has_duplicates_2, L2))  # append running time to y


##### Plot datasets
plt.figure()  # create a new figure
plt.scatter(
    x, y1, c="r", marker="x", label="has_duplicates_1"
)  # add scatter plot to figure
plt.scatter(
    x, y2, c="b", marker="o", label="has_duplicates_2"
)  # add scatter plot to figure
plt.ylabel("running time (s)")  # label y axis
plt.legend()  # add legend to figure
# plt.show()                                                          # show figure on local computer
plt.savefig("dups")  # save figure

# Note: You can either use plt.show() or plt.savefig(). Using both does not work.
