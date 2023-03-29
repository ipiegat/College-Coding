import os
import csv
import glob


def price_to_profit(prices):

    # create empty list
    daily_change = []
    # iterate though list of prices with indices
    for i in range(len(prices) - 1):
        # create current and next day variables
        current_day_price = prices[i]
        next_day_price = prices[i + 1]

        # next_day - current_day is difference in price
        daily_change.append(next_day_price - current_day_price)

    return daily_change


def max_profit(prices):

    # base case 1: if there is only one window to buy/sell then that is the profit
    if len(price_to_profit(prices)) == 1:
        return price_to_profit(prices)[0]

    # base case 2: if there is only a single day revenue would subtract itself
    if len(prices) == 1:
        return 0

    # splitting prices into two lists, one on left one on right
    # recursively, both will get smaller until a base case is found
    left = prices[: len(prices) // 2]
    right = prices[len(prices) // 2 :]

    # max and min values for when maximum profit buy/sell dates are on opposing sides
    minL = min(left)
    maxR = max(right)

    # maximum profit when buying and selling on the left,
    mpl = max_profit(left)
    # maximum profit when buying and selling on the right,
    mpr = max_profit(right)
    # maximum profit when buying on the left and selling on the right (maximum profit BOTH)
    mpb = maxR - minL

    # return the highest possible profit out of all three scenarios
    return max([mpl, mpr, mpb])


def max_profit_center(prices):

    left = prices[: len(prices) // 2]
    right = prices[len(prices) // 2 :]
    median = prices[len(prices) // 2]

    # sell on the median, so buy from the left
    pa = median - min(left)

    # buy on the median, so sell from the right
    pb = max(right) - median

    # buy before the median, but sell after
    pc = max(right) - min(left)

    # return largest profit
    return max([pa, pb, pc])


# Test code on 6 years of BitCoin data


bitcoin_prices = []
# files sorted into list by year
bitcoin_files_by_year = sorted(glob.glob("bitcoin_prices/*.csv"))
# iterate through file list
for filepath in bitcoin_files_by_year:
    with open(filepath) as file:
        csvreader = csv.DictReader(file)
        for row in csvreader:
            # append dictionary VALUES, or bitcoin prices, to bitcoin_prices list
            bitcoin_prices.append(float(row["Open"].replace(",", "")))
