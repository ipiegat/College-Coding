import unittest
from hw2a import *


class TestChessBoard(unittest.TestCase):
    def test_valid_moves(self):
        horse = (1, 1)
        test1 = valid_moves(horse)
        self.assertEqual(test1, {(3, 2), (2, 3), (0, 3), (3, 0)})

        horse = (3, 7)
        test2 = valid_moves(horse)
        self.assertEqual(test2, {(1, 6), (4, 5), (2, 5), (5, 6)})

    def test_solveable(self):
        horse = (2, 3)
        pawns = {(4, 4), (6, 5)}
        test1 = solveable(pawns, horse)
        self.assertEqual(test1, True)

        horse = (2, 3)
        # pawns = {(2, 1), (4, 3), (2, 5)}
        # test2 = solveable(pawns, horse)
        # self.assertEqual(test2, False)


if __name__ == "__main__":
    unittest.main()
