"1. Define Class, Instance, Inheritance, Composition, and Polymorphism, with examples."

# Class: A group of relating data and functions of which objects are created

# Instance: An object that belongs in a class (see create_list())

# Inheritance: Using or extending features of another class 

# Composition: Calling/referencing another class as an instance variable in a separate class

# Polymorphism: Something that has many different forms, such as the "+" operator works differently with 
# integers and strings

class example(): # class, superclass
    def __init__(self):
        self.end = 0
        self.integers = []
        self.overriding = "Not overriden yet"
    
    def create_list(self, n): #instance
        self.end = n
        for i in range(n):
            self.integers.append(i)

        return self.integers

class example2(example): # inheritance, subclass
    def __init__(self):
        super.__init__()
        self.overriding = "Overridden" # method overriding
    
    def reverse_list(self):
        obj1 = example() #composition

        return obj1

obj2 = example()
obj2.create_list()
obj2.create_list(20) # method overloading

"2. Define encapsulation, subclass, superclass, method overloading and method overriding with examples."

# Encapsulation: Grouping up variables/methods into a single thing like a class (look above)

# Subclass: A class which inherits a super class

# Superclass: A class being inherited by another

# Method Overloading: Calling the same method in different ways

# Method Overriding: When the child class can overwrite data in the parent class

"3. Calculate the time complexity of the following codes."

#Program 1
def print_f(data):
    n = len(data) # 1
    i = 1 # 1
    while i <= n: # n
        i = i*2

def calc_data(data):
    for i in range(1, len(data)): # n-1
        print_f(data) # 1

"Big-O notation: O(nlogn)"

#Program 2
N = int
for i in range(0, N): # N
    for j in range(N, i, -1): # N - i
        a = a + i + j # 3

for j in range(0, N/2): # N/2
    b = b + i + j # 3

"Big-O notation: O(N^2)"