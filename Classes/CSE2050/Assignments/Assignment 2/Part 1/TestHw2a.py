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

        horse = (-4, 6)
        test3 = valid_moves(horse)
        self.assertEqual(test3, "Horse is not on the board")

    def test_solveable(self):
        horse = (2, 3)
        pawns = {(4, 4), (6, 5)}  # both pawns can be taken, thus True
        test1 = solveable(pawns, horse)
        self.assertEqual(test1, True)

        horse = (0, 0)
        pawns = {(2, -1), (4, 0)}  # (2, -1) is not on the board, thus False
        test2 = solveable(pawns, horse)
        self.assertEqual(test2, False)

        horse = (4, 4)
        pawns = {(6, 5), (4, 4), (2, 6)}  # impossible combination to solve, thus False
        test3 = solveable(pawns, horse)
        self.assertEqual(test3, False)


if __name__ == "__main__":
    unittest.main()
