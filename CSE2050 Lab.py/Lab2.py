class Polygon:
    def __init__(self, nbr_sides):
        self.nbr_sides = nbr_sides

    def whoamI(self):
        if self.nbr_sides == 3:
            return "Triangle"
        if self.nbr_sides == 4:
            return "Rectangle"

    def howmanysides(self):
        return self.nbr_sides

    def area(self):
        return "No area"

    def perimeter(self):
        return "No perimeter"


class Rectangle(Polygon):
    def __init__(self, breadth, length):
        self.breadth = breadth
        self.length = length

    def area(self):
        area = self.breadth * self.length
        return area

    def perimeter(self):
        perimeter = 2 * (self.length + self.breadth)
        return perimeter


class Triangle(Polygon):
    def __init__(self, a, b, c):
        self.a = a
        self.b = b
        self.c = c

    def area(self):
        s = (self.a + self.b + self.c) / 2
        area = (s * (s - self.a) * (s - self.b) * (s - self.c)) ** (1 / 2)
        return area

    def perimeter(self):
        perimeter = self.a + self.b + self.c
        return perimeter
