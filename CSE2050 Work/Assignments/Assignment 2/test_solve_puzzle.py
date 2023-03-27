import unittest
from max_profit import price_to_profit, max_profit, max_profit_center


def max_profit_brute(L):
    """Finds maximum profit. Assumes L is a list of profits (i.e. change in price every day), not raw prices"""
    n = len(L)
    max_sum = 0  # assume we can at least break even - buy and sell on the same day
    # outer loop finds the max profit for each buy day
    for i in range(n):
        # total profit if we bought on day i and sold on day j
        total = L[i]
        if total > max_sum:
            max_sum = total

        for j in range(i + 1, n):
            total += L[j]  # total profit if we sell on day j
            # we assume L[j] is the profit if we bought on day j-1 and sold on day
            # j i.e., L is the change in value each day, relative to the day before

        if total > max_sum:
            max_sum = total

    return max_sum


class TestSolvePuzzle(unittest.TestCase):
    def test_price_to_profit(self):
        prices = [1, 2, 4, 7, 9]
        res = price_to_profit(prices)
        self.assertEqual(res, [1, 2, 3, 2])

    def test_max_profit(self):
        prices = [1, 2, 4, 7, 9]
        res = max_profit(prices)
        truth = max_profit_brute(price_to_profit(prices))
        self.assertEqual(res, truth)
    
    def test_max_profit_center(self):
        prices = [1, 2, 4, 7, 9]
        res = max_profit_center(prices)
        self.assertEqual(max_profit(prices), res)
        


if __name__ == "__main__":
    unittest.main()
