from solve_puzzle import solve_puzzle as puzzle
import unittest

class TestSolvePuzzle(unittest.TestCase):
        def testClockwise(self):
            """Tests a board solveable using only CW moves"""
            test = puzzle([1, 2, 3, 1])
            self.assertEqual(test, True)

        def testCounterClockwise(self):
            """Tests a board solveable using only CCW moves"""
            test = puzzle([1, 0, 3, 1])
            self.assertEqual(test, True)

        def testMixed(self):
            """Tests a board solveable using only a combination of CW and CCW moves"""
            test = puzzle([2, 0, 3, 1, 0])
            self.assertEqual(test, True)

        def testUnsolveable(self):
            """Tests an unsolveable board"""
            test = puzzle([0, 0, 0, 0, 0, 0])
            self.assertEqual(test, False)


unittest.main()