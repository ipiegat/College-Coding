"1. Define Class, Instance, Inheritance, Composition, and Polymorphism, with examples."

# Class: A group of relating data and functions of which objects are created

# Instance: An object that belongs in a class (see create_list())

# Inheritance: Using or extending features of another class 

# Composition: Calling/referencing another class as an instance variable in a separate class

# Polymorphism: Something that has many different forms, such as the "+" operator works differently with 
# integers and strings

class example(): # class
    def __init__(self):
        self.end = 0
        self.integers = []
    
    def create_list(self, n): #instance
        self.end = n
        for i in range(n):
            self.integers.append(i)

        return self.integers

class example2(example): # inheritance
    def __init__(self):
        super.__init__()
    
    def reverse_list(self):
        obj1 = example() #composition

        return obj1


"2. Define encapsulation, subclass, superclass, method overloading and method overriding with examples."








