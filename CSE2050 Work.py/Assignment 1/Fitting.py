from scipy import optimize
from matplotlib import pyplot as plt

# linear fitting function
# the first parameter of a fitting funciton must be x
# subsequent parameters are automatically adjusted by curve_fit
def const(x, m):
    return m


def lin(x, m, b):
    return m * x + b


def quad(x, m, b, z):
    return m * x**2 + b * x + z


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
    plt.plot(xdata, y_fit_quad, c ="r", label = "Quadratic")
    plt.plot(xdata, y_fit_lin, c = "g", label = "Linear")
    plt.xlabel("n")
    plt.ylabel("Duration (s)")
    plt.title("Best Fit")
    plt.legend()
    #plt.show()
    plt.savefig("bestfit")


def se(ydata, y_fit):
    result = 0
    for i in range(len(ydata)):
        result += (ydata[i] - y_fit[i]) ** 2

    return result


def mse(ydata, y_fit):
    N = len(ydata)
    result = (1 / N) * se(ydata, y_fit)

    return result


def rms(ydata, y_fit):
    result = (mse(ydata, y_fit)) ** (1 / 2)

    return result


def fit_data(func, xdata, ydata):
    params, _ = optimize.curve_fit(func, xdata, ydata)
    y_fit = []

    for x in xdata:
        y_fit.append(func(x, *params))

    rms2 = rms(ydata, y_fit)

    return params, rms2, ydata


# generate data on y = 1*x + 0, then add some "noise"
xdata = [i for i in range(10)]
ydata = [i for i in range(10)]
ydata[1] = 2
ydata[8] = 7

print(fit_data(const, xdata, ydata))
