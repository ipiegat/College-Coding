"""
Class 3 Notes: 1/26/2023

Composition: This concept lets us create complex types by combining objects of different classes
    - We cam call/reference one or more objects of another class as an instance variable in the current class
    - Composite Class: The class which contains an object of another class -> class A
    - Component Class: The class which is being referenced to create an instance within another class -> class B

Inheretance vs Composition:
    - Inheritance is used when we want the functionality of another class and extend it further by adding additional
    attributes or by overriding methods
    - Composition
"""

class Component:
    def __init__(self):
        print("Component class is created")

    def cmpnt(self):
        print("Method from component class is running")

class Composite:
    def __init__(self):
        print("Composite class is created")
        self.obj1 = Component()
    
    def cmpst(self):
        self.obj1 = Component()
        print("Method from composite class is running")

composite_obj = Composite()
composite_obj.cmpnt()

"""
Polymorphism: Something that has many different forms
    - It refers to use a single type of entity (method, operator or object) to represent different types in different
    scenarios
        - Example: "+" operation in python works with strings and integers

Testing:
    - Assert statement raises an error if he predicate is a failure
"""

class abc:
    def __init__(self, num):
        self.num = num
    
    def double(self):
        return self.num + 2

obj = abc(4)

assert(obj.double() == 8) #compares code value to wanted value. can have multiple in a row but all must pass
print("Test Passed!") # if above statement is true, print statement executes. if not error will pop up

"""
Unit Testing with unittest:
    - Bigger software programs are usually tested by a procesdure called unit testing
"""

pairs = {"Sun":"Sunday", "Mon": "Monday", "Tue": "Tuesday", "Wedn": "Wednesday", "Thur":"Thursday", "Fri": "Friday", "Satu": "Saturday"}
class DaysOfTheWeek:
    def __init__(self, abbreviated_name):
        self.abbreviated_name = abbreviated_name
    
    def full_name(self):
        return pairs[self.abbreviated_name]
    
Day = DaysOfTheWeek("Sun")
print(Day.full_name())

import unittest

class TestDaysOfTheWeek(unittest.TestCase):
    def test_days(self):
        day = DaysOfTheWeek("Sun")
        self.assertEqual(day.full_name(), "Sunday")

        day = DaysOfTheWeek("Mon")
        self.assertEqual(day.full_name(), "Monday")
    
unittest.main()

#--------------------------------------------------------

"""
Class 2 Notes: 1/24/2023

Encapsulation:
    1) Wrapping up the data and the methods in a single unit
        - CLASSES
    2) Draw a boundary between a public and a private data
        - Deciding what data to make visible to users and what to remain hidden
        - Java and C++ can explicitly declare public/private attributes
        - No forced way of doing this in python
        - A convention is developed by declaring names of private variables starting with "_"
Inheritance:
    1) New class may not be needed to create from scratch
    2) Can use features/ attributes of already existing class as a base to create new class
    3) Best explained as enherenting features of existing class, say A into B
    4) Great example of code 'reuse'
    5) Also called "is a" realtionship
        - Child class is an instance of parent class
    
"""

class Person():
    def __init__(self, name, gender, age):
        self.name = name
        self.gender = gender
        self.age = age

class Faculty(Person): # inherit parent class attributes
    def __init__(self, name, gender, age, teaching):
        self.teaching = teaching
        super().__init__(name, age, gender) # initiliazer of superclass

class Student(Person):
    def __init__(self, name, gender, age, courses):
        self.courses = courses
        super().__init__(name, age, gender) 

faculty1 = Faculty("Isaac", "M", "18", "CSE") # creates error, look line 38
print(faculty1.age)

#--------------------------------------------------------

"""
Class 1 CSE 1010 Review: 1/19/2023

1. def get_letter_grade(num_grade):

2. calc_calories(21)

3. false

4. 43, 21

"""

#--------------------------------------------------------

