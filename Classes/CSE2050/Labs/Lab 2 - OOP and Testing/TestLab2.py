import unittest
from Superclass import Polygon, Triangle, Rectangle


class TestLab2(unittest.TestCase):
    def test_init(self):

        a1 = Polygon(3)
        self.assertEqual(a1.whoamI(), "Triangle")
        self.assertEqual(a1.howmanysides(), 3)
        a2 = Polygon(4)
        self.assertEqual(a2.whoamI(), "Rectangle")
        self.assertEqual(a2.howmanysides(), 4)

    def test_area(self):

        t1 = Triangle(3, 4, 5)
        self.assertEqual(t1.area(), 6)
        r1 = Rectangle(2, 4)
        self.assertEqual(r1.area(), 8)

    def test_perimeter(self):

        t1 = Triangle(3, 4, 5)
        self.assertEqual(t1.perimeter(), 12)
        r1 = Rectangle(2, 4)
        self.assertEqual(r1.perimeter(), 12)


if __name__ == "__main__":
    unittest.main()
