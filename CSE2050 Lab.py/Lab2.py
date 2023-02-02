class Polygon:
    def __init__(self, nbr_sides):
        self.nbr_sides = nbr_sides

    def whoamI(self):
        pass

    def howmanysides(self):
        pass

class Rectangle(Polygon):
    def __init__(self, breadth, length):
        self.breadth = breadth
        self.length = length
    
    def area(self, breadth, length):
        pass
        area = breadth * length
        #return area
    
    def perimeter(self, breadth, length):
        pass
        #perimeter = (breadth*2)+(length*2)
        #return perimeter

class Triangle(Polygon):
    def __init__(self, a, b, c):
        self.a = a
        self.b = b
        self.c = c
    
    def area(self, a, b):
        pass
        #area = 1/2(a*b)
        #return area
    
    def perimeter(self, a, b, c):
        pass
        #perimeter = a + b + c
        #return perimeter
    





