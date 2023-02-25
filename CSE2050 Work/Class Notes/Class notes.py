"""Class 10 Notes: 2/23/2023

Recursion: Basic Rules
    - Have a Base Case

Fibonacci Sequence:
    - A series of numbers in which a given number is a sum of previous two numbers
        - f(n) = f(n-1) + f(n-2)

"""


def fibanacci_sequence(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    else:
        return fibanacci_sequence(n - 2) + fibanacci_sequence(n - 1)


# Time complexity for fib sequence:
# T(k) = T(k-1) + T(k-2) + 1
# T(k) = 2T(k-1) + 1
# T(1) = 2T(0) + 1 = 1
# T(2) = 2T(1) + 1 = 2 + 1 = 3


def factorial(n):
    answer = 1
    for i in range(n, 1, -1):
        answer *= i
    return answer


def fact_recr(n):
    if n >= 1:
        return n * fact_recr(n - 1)
    else:
        return 1


def sum(k):
    if k > 0:  # base case
        return sum(k - 1) + k
    return 0


import sys

sys.setrecursionlimit(50)
# --------------------------------------------------------------------------------------


"""Class 9 Notes: 2/21/2023

Doubly Linked List:
    - Maintain position of the next and previous node 
    - Provides O(1) time complexity for all operations
    - Two dummy nodes:
        - header, trailer
        - The head and tail never chance, only elements/nodes between them
        - All insert operations add between existing nodes
        - As with all delete operations
    - Insert node in doubly linked list
        - Create a new node with reference of predecessor and successor nodes
        - Update next and prev pointers of predecessor and sucessor nodes to the new node
    - Deletion of a node
        - Link neighbors of deleted node with each other


"""


class _Node:
    def __init__(self, prev, element, next):
        self._prev = prev
        self._element = element
        self._next = next


class DoublyLinkedList:
    def __init__(self):
        self._header = _Node(None, None, None)
        self._trailer = _Node(None, None, None)
        self._header.next = self._trailer
        self._trailer.prev = self._header
        self._size = 0

    def insert_between(self, predecessor, element, successor):
        newest = _Node(predecessor, element, successor)
        predecessor._next = newest
        successor._prev = newest
        self._size += 1

    def delete_node(self, node):
        predecessor = node._prev
        successor = node._next
        predecessor._next = successor
        successor._prev = predecessor
        self._size -= 1

        element = node._element
        node._prev = node._next = node._element = None  # garbage collection
        return element


"""Module 5: Recursion and Dynamic Programming

    - Recursion: A method of solving a problem with the help of a function, when the function calls itself
    - Function Call Stack: A function which recursively calls itself forever
        - Detects recursion with RecursionError

"""


def sum(k):  # infinitely looping function
    if k > 0:
        return sum(k - 1) + k
    return 0


# --------------------------------------------------------------------------------------

"""Class 8 Test Review Note: 2/14/2023

Module 1:
    - Class: Template to create objects
    - Method: functions defined in a class
    - Attributes: data/features of class
    - Instantiation: creation of an object/instance of a class
    - Inheritance: Inheriting or extending the existing features of another class
        - inherited class -> parent / base / super class
        - inheriting class -> child / derived / sub class
    - Composition: Creating an instance of a class within another class
        - Composite class -> class which contains an object of another class
        - Component class -> class being referenced in another class
        - class B():
            - obj = A()
    - Polymorphism: reuse and renaming 

Module 2: Testing
    - assert statements
        - all tests must pass or returns false
        - does not specify where error occurs
    - unitttest
        - runs all tests even if any test fails
        - specify where the failure occured
    - test driven development
        - tdd is based on red-green-refactor phases
        - red: fails
        - green: passes
        - refactor: clean up code, remove clutter/duplication

Module 3: Running time analysis
    - Performance analysis via measuring execution time
        - does not give us accurate performance because of different factors
    - asympotic analysis
    - big O notation
        - consider highest power element

Module 4: Linear Data Structures
    - Stacks - LIFO - LAST IN FIRST OUT
        - PUSH, POP, PEEK time complexity O(1)
    - Queues - FIFO - FIRST IN FIRST OUT
        - Enqueue, dequeue, first/peek
            - dequeue time complexity O(n), others O(1)
    - Linked Lists
        - Minimally, linked list must keep a reference of head node
        - Deleting element from the tail of linked list is O(n) time complexity

"""

# --------------------------------------------------------------------------------------

"""Class 7 Notes: 2/9/2023

Abstract Data Types (ADT)
    - Stacks - LIFO
        - Operations: PUSH, POP, PEEK, IS_EMPTY, LEN
        - Cost: O(1)
    - Queues - FIFO
        - Operations: ENQUEUE, DEQUEUE, FIRST, IS_EMPTY, LEN
        - Cost: Dequeue -> O(n)
        - To overcome this, we made use of the head variable to dequeue the element in the front of queue

Deque ADT
    - Acts like stack and queue
        - Add or remove elements from both the beginning and the end
        - addfirst(), addlast(), removefirst(), removelast(), len()
        - Uses list data structure so shifting left or right
        - INSTEAD arrange data in NODES
            - Data (Head to Tail) and address -> Linked Lists ADT
            - Use a class Node"""


class _Node:
    def __init__(self, element, next):
        self._element = element
        self._next = next


"""Linked Lists ADT: Singly Linked List
    - Simplest form of linked lists
    - First node is the head node, last node is the tail node
    - Tail node is determined if next none = None
    - Keep reference of head node and tail node
    - When creating a new element, point it to Head. Then that element is updated to be Head. 
"""
L = []
# create new HEAD
newest = _Node()  # create a node with an element
newest._next = L.head  # set newest node next reference to the current head node
L.head = newest  # set variable to "head" to refer the newest node as head node
L.size += 1  # update the size of the list

# create new TAIL
newest = _Node()  # create node with element
newest.next = None  # set the newest code next reference to None
L.tail.next = (
    newest  # set the next node reference of current tail to point to the newest node
)
L.Tail = newest  # set the variable "tail" to reference to newes node
L.size += 1  # update size of list

# start with an instance of LinkedStack with head = None


class LinkedStack:
    def __init__(self):
        self._head = None
        self._tail = None
        self._size = 0

    def push(self, item):
        head = _Node(item, head)
        item = self._tail
        self._size += 1

    def pop(self):
        read_element = head
        head = head._next
        self._size -= 1
        return read_element


"""Queue ADT as Linked List
1. Start off by creating an instance of LinkedQueue with:
    head = None
    tail = None
2. Enqueue operation
    newest = _Node("A", None)
    if it is the first element then 
        head = newest
    set the element as a a Tail
        tail = newest
3. Enqueueing another element
    newest = _Node("B", None)
    if it is the first element then 
        head = newest
    else
        tail._next = newest
    set the element as a tail element
    newest = self._tail(newest)
4. Dequeue read the element
        read_element = head._element
    update the head variable to be set to the next node
        head = head._next
        if it was the last element in the queue
            tail = None
    reduce the size of queue
    return read_element

"""

# --------------------------------------------------------------------------------------

"""Class 6 Notes: 2/7/2023

Stack ADT: Operations
    - stack.push(integer) -> goes to top of stack
    - stack.pop() removes element at top of stack
    - stack.peek() returns element at top of stack
    - stack.is_empty() returns true if stack is empty, false if not
    - stack.len() return number of elements in a stack

Queue ADT: A collection of objects that are inserted and removed according to the first in first out principle (FIFO)
    - Elements can be inserted in back of que

Queue Operations:
    - Q.enqueue(e) add element to back of que
    - Q.dequeue() removes first added value and returns it

"""


class Q:
    def __init__(self):
        self.L = []
        self._head = 0

    def enqueue(self, item):
        self.L.append(item)

    def dequeue(self):
        front_item = self.peek()
        self._head += 1
        return front_item
        # self.L.pop(0) is inefficient, so simply return

    def peek(self):
        return self._L[self._head]


# --------------------------------------------------------------------------------------

"""
Class 5 Notes: 2/2/2023
"""


def sum(k):
    total = 0  # 1
    for i in range(0, k + 1):
        total += i  # 2k

    return total  # 1


# 2k + 2


def sum_improved(k):
    total = k * (k + 1) // 2
    return total


# 5

"""
Big-O Notation: Ignore terms to a lower power once number is large enough

f(n) = O(g(n))

Example:

f(n) = 3n^2 + 2n + 1 can be represented as O(n^2) only when f(n) <= c * g(n) which is 4 * n^2
n = 1
3(1)+2(1)+1 = 7 /// 4*1 = 4

n = 2
3(2)+2(2)+1 = 17 /// 4*2^2 = 16

n = 3
3(3)+2(3)+1 = 34 /// 4*3^2 = 36 so CONDITION is satisfied this n_initial = 3

"""


def duplicates_1(L):
    n = len(L)
    for i in range(n):
        for j in range(i, n):
            if i != j and L[i] == L[j]:
                return True

    return False


# n^2/2 - n/2 + 3

# O(n^2)

# ------------------------------------------------------------------------------------

"""
Class 4 Notes: 1/31/2023

Test Driven Development:
    - Red: The test fails
    - Green: You get the tests to pass
    - Refactor: You clean up the code, removing clutter/duplication

Time Module:
"""


def duplicates_1(L):
    n = len(L)  # 2
    for i in range(n):  # n
        for j in range(
            i, n
        ):  # n - i, i reduces comparison time by comparing each pair once
            if i != j and L[i] == L[j]:  # 2
                return True  # not executed in worst case scenario

    return False  # 1


# Total cost = 2+n(n(2))+1 = 2n^2 + 3 without (i, n)

import time

# from duplicates immport duplicates_1

n = 1000
for i in range(5):
    start_time = time.time()
    duplicates_1(list(range(n)))
    end_time = time.time()
    timetaken = end_time - start_time

    print("Time taken for n = ", n, ":", timetaken)

# create improved algorithm for duplicates to reduce time

"""
Asymptotic Analysis:
    - Performance is determined by the size of an input and the number of operations executed by algorithm
    - L.pop(2) -> n - i or 5 - 2 = 3 atomic operations
    - See duplicates_1 comments
"""

# ------------------------------------------------------------------

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

assert (
    obj.double() == 8
)  # compares code value to wanted value. can have multiple in a row but all must pass
print(
    "Test Passed!"
)  # if above statement is true, print statement executes. if not error will pop up

"""
Unit Testing with unittest:
    - Bigger software programs are usually tested by a procesdure called unit testing
"""

pairs = {
    "Sun": "Sunday",
    "Mon": "Monday",
    "Tue": "Tuesday",
    "Wedn": "Wednesday",
    "Thur": "Thursday",
    "Fri": "Friday",
    "Satu": "Saturday",
}


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

# --------------------------------------------------------

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
    5) Also called "is a" relationship
        - Child class is an instance of parent class
    
"""


class Person:
    def __init__(self, name, gender, age):
        self.name = name
        self.gender = gender
        self.age = age


class Faculty(Person):  # inherit parent class attributes
    def __init__(self, name, gender, age, teaching):
        self.teaching = teaching
        super().__init__(name, age, gender)  # initiliazer of superclass


class Student(Person):
    def __init__(self, name, gender, age, courses):
        self.courses = courses
        super().__init__(name, age, gender)


faculty1 = Faculty("Isaac", "M", "18", "CSE")  # creates error, look line 38
print(faculty1.age)

# --------------------------------------------------------

"""
Class 1 CSE 1010 Review: 1/19/2023

1. def get_letter_grade(num_grade):

2. calc_calories(21)

3. false

4. 43, 21

"""

# --------------------------------------------------------
