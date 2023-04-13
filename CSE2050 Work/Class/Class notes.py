"""Class 18 Notes: 4/11/2023

Module 9: Trees
    - Tree is an abstract data type that stores elements hierarchically
    - Non-linear data structure, relationship between objects/data are:
        - NOT defined as "before and after" relationship
        - Defined as "above and below" relationship
        - Examples:
            - Organizational charts, file systems
        - Each element in a tree has a parent element and zero.more children elements, 
          except the first/top element which is called the root. 
    - Termonology:
        - Root: Highest-most node without parent
        - Edge: Connection between two nodes to show relationship between them
        - Path: A path is an orderd list of nodes connected by edges
        - Parent:
        - Descendant: All nodes for which there is a path from x (child, grandchild, etc)
        - Ancestor: Opposite of descendent (parent, grandparent)
        - Leaf Node: last node in the tree, or nodes with no children
        - Subtree: A set of nodes and edges comprised of a parent and 
        - Height: number of edges in the longest path from the node x to a leaf
        - Depth/level: Number od edges in path from root to x
        - Degree of node: The number of the node's children
        - In a tree, there must only be a single path from the root node to any other node
    - Trees as Lists
        - Tree can be defined recursively as a root with zero or more children
            - Each child can be a subtree
        - T = ['C', 
                  ['A',
                      ['P', 'N']
                  ]
    - ADT 
        - __init__(L): initializes a new tree with data, children (list) and parent
        - add_child(): 
        - get_level():
        - __str__():
    - Binary Search Trees
        - Data structures to organize data efficiently
        - Every node in the tree can have at most 2 children (left and right child)
            - Left child is amller than the parent node
            - Right child is greater than the parent node
        - New data is placed in sorted order so that the search and other operations can use the
          princible of binary search with O(logn) running time
        - We can access the root node exclusively as the same we can access head node of linked list
        - Inserting element would take O(logN) time complexity 
        - Balanced tree (left and right nodes contain approx. same number of children)
            - operations are O(logN)
        - Imbalanced tree (number of children on both sides differ significantly)
            - operations O(N) time complexity 
        - Operations:
            - insert
            - search (min/max)
            - delete
            - traverse
        - Implementation:
            - Create node class
                - Actual data
                - Parent node
                - Left child
                - Right child
            - Operations:
                - Insert
                    - Add root node if it does not exist
                    - Chec, if the new element is greater/smaller than current parent
                    - If left/right child does not exist, add node to correct side
                    - If child node exists, recursively execute steps 2 and 3

"""


class BSTNode:
    def __init__(self, data, parent=None):
        self.data = data
        self.parent = parent
        self.left = None
        self.right = None


class BinarySearchTree:
    def __init__(self, root=None):
        self.root = root

    def insert(self, data):
        if self.root is None:
            self.root = BSTNode(data)

        else:
            self._add_child(data, self.root)

    def _add_child(self, data, p_node):
        if data == p_node.data:
            print("duplicates not alowed")
            return

        if data < p_node.data:
            if p_node.left:
                self._add_child(data, p_node.left)

            else:
                p_node.left = BSTNode(data, p_node)

        else:
            if p_node.right:
                self._add_child(data, p_node.right)
            else:
                p_node.right = BSTNode(data, p_node)

    def search(self, node):
        pass

    def delete(self, node):
        pass

    def traverse(self):
        pass


class TreeNode:
    def __init__(self, data):
        self.data = data
        self.children = []
        self.parent = None

    def get_level(self):
        level = 0
        node_parent = self.parent
        while node_parent != None:
            level += 1
            node_parent = node_parent.parent

        return level

    def add_child(self, child):
        child.parent = self
        self.children.append(child)


# --------------------------------------------------------------------------------------

"""Class 18 Notes: 4/6/2023

Hash Tables
    - Collision Handling Schemes Separate Chaining
        - Have each bucket M[j] store its own container to carry multile (k, v) items
            - M is the array of buckets
            - j is the location of jth bucket
        - h(k) = j -> hash code
        - Implementation
            1. Create a HashTale of size 10
            2. Create 10 buckets (bucket array) each containing secondary structure (ListMapping)
            3. Putting a key-value pair in the bucket
                - Get the bucket first
                    - Generate a hash function for the key -> using Python's built-in hash function
                    - Take modulo with the size of a hash table to calculate jth index (bucket location)
                    - Return jth bucket
                - Put the key_value pair in the jth bucket (put method)
            4. Retrieving a value
                - Get the bucket (using get method) and return the value associated with the key
        - Time Complexity
            - Time to search for bucket is O(1)
            - Locating element in bucket is O(n)
        - A ratio lamda = n/N is called "Load Factor"
            - "n" items of map in a bucket array capacity of "N"
            - Bounded by a small constant (preferably below 1)
            - Example:
                - n = 15
                - N = 10
                - lamda = 1.5 therefore collision 
        - Dynamic resizing - Double the size of the hash table when load factor increases beyond 1
            - Implement a method to double the size of hash table
                - Python resizes hash table when load factor > .66
            - After resizing, all items in old hash table have to be added to new one O(n)
        - Nice property of chaining method is its easy implementation
            - Drawback -> requires auxiliary data structure - list to hold items with colliding keys
            - For applications where space is an issue (like hand-held devices)
                - We can consider storing each item in a separate table slot
                - Load factor is always at most required to be 1
                - Dealing with "collisions" becomes more complicated
    - Collision-Handling Schemes Open Addressing
        - Linear Probing
            - Inserting an element (k, v) at M[j]
                - j is the index generated by hash fucntion
            - If jth slot i


"""


class HashTable:
    def __init__(self):
        self._htsize = 10
        self._buckets_array = [ListMapping() for i in range(self._htsize)]

    def put(self, key, value):
        bucket = self._get_bucket(key)
        bucket.put(key, value)

    def get(self, key):
        bucket = self._get_bucket(key)
        return bucket.get(key)

    def _get_bucket(self, key):
        j = hash(key) % self._htsize
        return self._buckets_array[j]


# --------------------------------------------------------------------------------------

"""Class 17 Notes: 4/4/2023

Module 8: Mapping and Hashing
    - Mapping: An association between two objects
        - Objects are also referred as "key-value" pair
        - The array of such key-value pairs are sometimes referred as "assofiative arrays" or "maps"
            - Dictionaries
            - Key must always be unique
        - Maps use an array-like syntax for indexing
            - Currency[ Greece ] tp access a value (currency) associated with key
            - Can be updated Currency[ Greece ] = new (updates value for greece) or creates new
        - Indices don't need to be consecutive or numeric
        - Applications
            - User data, map DNS hostname, 
    - Map ADT
        - get(k) method -> returns value associated with key, k, or error if not present
        - put(k, v) method
        - remove(k)
        - __contains__(k)
        - __len__()
        - _entry(k)
            - FIRST FOUR require list traversal
        - Minimal implementation using list
            - Create simple class to hold key-value variables as objects
    - Hast Tables
        - The most practical data structure to implement "map"
        - Used python's dict class implementation
        - Key -> Hash function -> Indices/code (hash codes)
        - The goal of hash function,h, is to map each key, k, to an integer in the range [0, N-1]
        - Many different strategies to generate hash code
            - Take ASCII value of all characters in a strong and calculate sum of them
                - "Tim" has ASCII value of 84 + 105 + 109 = 298
                - Store in N = 11 memory locations
                    - Take modulo with size M -> 298 % 11 -> 1
                - Can result in Hash Collision
        - Collision Handling Schemes
            - Conceptualize 
        


"""


class Entry:
    def __init__(self, key, value):
        self.key = key
        self.value = value

    def __str__(self):
        return str(self.key) + ":" + str(self.value)


class ListMapping:
    def __init__(self):
        self._map = []

    def get(self, key):
        for e in self._map:
            if e.key == key:
                return e.value

        raise KeyError

    def put(self, key, value):
        for e in self._map:
            if e.key == key:
                key.value = value
                return

        self._map.append(Entry(key, value))


# --------------------------------------------------------------------------------------

"""Class 16 Notes: 3/28/2023

Exam 2 review:
    - Module 5: Recursion and Dynamic Programming
        - FunctionCall Stack (LIFO) structure to hold recursive calls
        - Restricted to 1000 by default sys.setrecursion
        - Have a base case
            - Recursion calls
            - Recursion calls move towards base case
            - No base case leads to RecursionError
        - Memoization 
            - Avoid making function call again which has already been executed
            - Storing intermediate solution of subproblems and use later
            - Top down approach
        - Dynamic Programming
            - Bottom up approach using tabulation (iterative) method
    - Module 6: Searching and Sorting
        - Binary Search
            - Search for an element in a sorted array by dividing search interval in half
            - Start by examining the middle item -> return if it is the item
                - If the required item is less, disregard upper half. If greater, vice versa
                - Repeat until item is found or not found
                - O(n) time complexity with slicing, O(log(n)) without slicing
                    - n/(2^k) = 1
        - Bubble Sort Algorithm O(n^2)
            for el in range(len(L)-1)
                for i in range(1, len(L)-el)
        - Selection Sort Algorithm O(n^2)
            - We can find either smallest item and place at beginning or larger vice versa
            - Selection sort is better for applications where less number of write operations
            are required
        - Insertion Sort Algorithm
            - Online algorithm: sort array as it receives data (example: from web)
        - Bubble sort
            - Iterates over every pair in collection, swaps out of order pairs
            - After x iterations, the last x items are in their final (sorted) place
        - Selection sort
            - Iterates over every unsorted item in collection, selects the next smallest/biggest
    - Module 7: Divide and Conquer
        - Divide: Divide the input data D into two or more disjoint subsets, D1 and D2
        - Conquer: Recursively solve subproblems
        - Merge-Sort Algorithm O(m1 + m2) but total is O(nlogn)
             2^i * n/2^i -> O(n)
        - Quick-sort Algorithm
            - In-place implementation
            - Worst case runtime -> O(n^2)
    
"""


# logn time complexity
def binary_search_imprv(data, item, lower_index, upper_index, count=0):
    count += 1
    # gone through the whole list, return false
    if lower_index > upper_index:
        return False, count

    else:
        # split data into two
        mid_index = (lower_index + upper_index) // 2
        # if we just so happen to find the data, return true
        if data == data[mid_index]:
            return True, count
        # if data is smaller than mid_index, pass in lower half of the list
        elif data[item] < mid_index:
            return binary_search_imprv(data, item, lower_index, mid_index - 1, count)
        # if data is larger than mid_index, pass in upper half of the list
        elif data[item] > mid_index:
            return binary_search_imprv(data, item, mid_index + 1, upper_index, count)


# go through list and if value is smaller than the one on its left, swap -> O(n^2)
def insertion_sort(L):
    # assume first item is sorted, so begin there
    for i in range(1, len(L)):
        curNum = L[i]
        # iterate backwords beginning from left of curNum
        for j in range(i - 1, 0, -1):
            # if the number to the left of curNum is smaller,
            if L[j] < curNum:
                # swap numbers
                L[j + 1] = L[j]
            else:
                break


# find smallest item , swap into first position
def selection_sort(L):
    # iterate through list
    for i in range(0, len(L) - 1):
        # set min index
        minIndex = i
        # check the one to the right of min index
        for j in range(i + 1, len(L)):
            # if the one to the right is smaller
            if L[j] < L[minIndex]:
                # set smaller value to min index
                minIndex = j
            # if the new min index isn't equal to the last one
            if minIndex != i:
                # swap both of them
                L[i], L[minIndex] = L[minIndex], L[i]

    return L


def bubble_sort(L):
    for i in range(0, len(L) - 1):
        for j in range(len(L) - 1 - i):
            if L[j] > L[j + 1]:
                L[j], L[j + 1] = L[j + 1], L[j]

    return L


# divide and conquer, nlog(n), efficient for larger data sets
def merge(D1, D2, D):
    i = j = 0

    while i < len(D1) and j < len(D2):
        if D1[i] < D2[j]:
            D[i + j] = D1[i]
            i += 1
        else:
            D[i + j] = D2[j]
            j += 1

    D[i + j :] = D1[i:] + D2[j:]


def merge_sort(D):
    if len(D) > 1:
        n = len(D) // 2
        D1 = D[:n]
        D2 = D[n:]
        merge(D1)
        merge(D2)
        D = merge(D1, D2, D)


# divide and conquer, recursive, efficient for larger data sets, worst case O(n^2) average case (nlogn)
# performance depends on pivot selection
def partition(D, L, H):
    pivotindex = (L + H) // 2
    # swap(pivotindex, high)

    border = L

    for j in range(L, H + 1):
        if D[j] <= D[H]:
            border += 1

    return border - 1


def quickSort(D, L_idx, H_idx):
    if L_idx < H_idx:
        pivot = partition(D, L_idx, H_idx)
        quickSort(D, L_idx, pivot - 1)


# --------------------------------------------------------------------------------------

"""Class 15 Notes: 3/23/2023

Last class summary:
    Quadratic Sorting Alg: O(n^2)
        - Bubble sort (swap instantly)
        - Selection sort (keep on recording index and swap at the end of inner loop)
        - Insertion sort( check all preceding elements)
            - Swapped elements may not be at their place until the end
        - Divide and Conquer:
            - Divide the data
            - Conquering using recursion
            - Combine
        - Merge sort algorithm
            - Time complexity O(nlogn)

Quick-Sort Algorithm:
    - Divide: Pick a random element x (called pivot)
      from D; then partition D into 
        - L elements -> less than x
        - E elements -> equal to x
        - G elements -> greater than x
        - Nothing needs to be done if D has one or less element
    - Conquer: Recursively sort sequences L and G
    - Combine: Join L, E, and G
    - Any element can be taken as a pivot element - first, last, or middle

Quick-sort: In-place Implementation
    - Uses indexes instead of creating entirely new lists

"""
# Algorithm quickSort(D)
# Input: sequence D with n elements
# Output: sequence D sorted

# if D.size() > 1
# pivot <- pick x from D
# L <- elements less then x
# E <- equal to x
# G <- elements greater then x
# L = quickSort(L)
# G = quickSort(G)
# return L + E + G
# else:
# return D

# quickSort(D, L_idx, H_idx) in-place implementation
# if L_ifx < H_idx
# pivot = partition(D, L_idx, H_idx)
# quickSort(D, L_idx, pivot-1)
# quickSort(D, pivot+1, H_idx)
# end


def partition(D, L, H):
    pivotindex = (L + H) // 2
    # swap(pivotindex, high)

    i = L

    for j in range(L, H + 1):
        if D[j] <= D[H]:
            i += 1

    return i - 1


def quickSort(D, L_idx, H_idx):
    if L_idx < H_idx:
        pivot = partition(D, L_idx, H_idx)
        quickSort(D, L_idx, pivot - 1)


# --------------------------------------------------------------------------------------

"""Class 14 Notes: 3/21/2023

More sorting algorithms:
    - Insertion Sort
        - another O(n^2) time complexity
        - easy to implement
        - more efficient than bubble sort and selection sort
            - selection sort is better for applications where less number of write operations
            are required
        - compare current element with procedeing elements
            - if current element is smaller than its preceding element -> swap
    - Online algorithm 0 sort array as it receieves data (example from web)

Module 7: Divide and Conquer
     1. Divide: Divide the input data into two or more disjoint subsets, D1 and D2
     2. Conquer: Recursively solve the subproblems associated with the subsets, D1 and D2
     3. Combine: Take the solutions to the subproblems (D1, D2) and merge them into a solution 
     to the original problem D

     Base case: Subproblems of a size 0 or 1

     Merge sorting algorithm: Based on divide and conquer paradigm
        - Divide: Partition D into two sequences D1 and D2 having n/2 elements in each
            - If D has zero or one item, return D as it is considered sorted
        
        - Conquer: Recursively sort D1 and D2
        - Combine: Merge D1 and D2 into a sorted sequence
    
    Time complexity:
        - 2^i * x * n/2^i -> O(n)
        - Stopping condition of recursion O(logn)
        - Total time complexity = O(nlogn)

"""

# if D.size() > 1
# (D1, D2) <- partition(D, n/2)
# mergesort(D1)
# mergesort(D2)
# D <- merge(D1, D2)


def merge(D1, D2, D):
    i = j = 0

    while i < len(D1) and j < len(D2):
        if D1[i] < D2[j]:
            D[i + j] = D1[i]
            i += 1
        else:
            D[i + j] = D2[j]
            j += 1

    D[i + j :] = D1[i:] + D2[j:]


def merge_sort(D):
    if len(D) > 1:
        n = len(D) // 2
        D1 = D[:n]
        D2 = D[n:]
        merge(D1)
        merge(D2)
        D = merge(D1, D2, D)


# --------------------------------------------------------------------------------------

"""Class 13 Notes: 3/9/2023

Sorting Algorithms
    - Bubble sort
    - Selection sort
        - Find smallest item and place it at beginning
        - or largest item and place it at the end
"""
L = []


def is_sorted(L):
    for i in range(len(L) - 1):
        for j in range(i + 1, len(L)):
            if L[i] > L[j]:
                return False
        return True


def is_sorted_better(L):
    for i in range(len(L) - 1):
        if L[i] > L[i + 1]:
            return False
        return True


def bubble_sort(L):
    for el in range(len(L) - 1):
        for i in range(len(L) - 1 - el):
            if L[i] > L[i + 1]:  # If two items are out of order
                L[i], L[i + 1] = L[i + 1], L[i]  # Switch them, time complexity O(n^2)


def selection_sort_min(L):
    for i in range(len(L) - 1):
        min_idx = i
        for j in range(i + 1, len(L)):
            if L[j] < L[min_idx]:
                min_idx = j

        L[i], L[min_idx] = L[min_idx], L[i]

    return L


def selection_sort_max(L):
    for i in range(len(L) - 1):
        max_index = 0
        for j in range(1, len(L) - i):
            if L[j] > L[max_index]:
                max_index = j

        L[-1 - i], L[max_index] = L[max_index], L[-1 - i]

    return L


# --------------------------------------------------------------------------------------


"""Class 12 Notes: 3/7/2023

Binary Search Algorithm: Search for an element in a sorted array by dividing search interval in half
    - Find middle item, find if > or < then cut out portion 
    - Repeat

^ Time complexity:
    - 0th iteration data size = n
    - 1st iteration data size = n/2 or n/(2^1)
    - 2nd iteratoin data size = n/4 or n/(2^2)
    - at kth iteration, the data size becomes 1
        - n/(2^k) = 1
        - n = 2^k
        - logn = log2^k or O(logn)

"""


def binary_search(data, item, count=0):
    count += 1
    if len(data) == 0:
        return False, count

    else:
        mid_index = len(data) // 2

        if item == data[mid_index]:
            return True, count

        elif item < data[mid_index]:
            return binary_search(
                data[:mid_index], item, count
            )  # because of slicing, O(n) time complexity

        elif item > data[mid_index]:
            return binary_search(
                data[mid_index + 1 :], item, count
            )  # instead pass index and not entire new list


def binary_search_imprv(data, item, lower_index, upper_index, count=0):
    count += 1

    if lower_index > upper_index:
        return False, count

    else:
        mid_index = (lower_index + upper_index) // 2

        if data == data[mid_index]:
            return True, count

        elif data[item] < mid_index:
            return binary_search_imprv(data, item, lower_index, mid_index - 1, count)

        elif data[item] > mid_index:
            return binary_search_imprv(data, item, mid_index + 1, upper_index, count)


def BS_iterative(L, item):
    lower, upper = 0, len(L)

    while upper - lower > 0:
        mid_index = (lower + upper) // 2

        if item == L[mid_index]:
            return True

        elif item < L[mid_index]:
            upper = mid_index

        else:
            lower = mid_index

    return False


# --------------------------------------------------------------------------------------

"""Class 11 Notes: 3/2/2023

Recursion
    base case
    recursive calls move towards base case

FunctionCall Stack

Dynamic Programming: Refers to an optimization over plain recursion
    - Avoid making a function call again which has already been executed by:
        - storing the intermediate solution of subproblems and use them later when needed
        - this is called Memoization

Two approaches of formulating a dynamic programming solution:
    1) Top-down approach: Use memoization
        - Create the fib sequence function
        - Create variable which will hold the returning value
            - Apppend variable to list if not already there
        - Repeat
    2) Bottom up approach using tabulation (iterative) method

Longest common subsequence: Problem of finding a longest subsequence 't' in a given set of
sequences (usually just two) S1 and S2, such that all characters in 't' appears in S1 and S2
in the same order
    - Example:
        S1: a. b. c. d
        S2: a. b, c, a, d
        longest common:  abc, abd
        2**n possible subsequences
    - Optimizing
        Compare if the last in each sequence are the same
            X[-1] == Y[-1]

"""


def fib_sequence(k, fib_array):
    if k in [0, 1]:
        fib_array[k] = k
        return fib_array[k]

    if fib_array[k] != None:
        return fib_array[k]
    fib_array[k] = fib_sequence(k - 1, fib_array) + fib_sequence(k - 2, fib_array)

    return fib_array


X = "abcd"
Y = "bc"


def LCS(X, Y):
    if X == "" or Y == "":
        return ""

    elif X[-1] == Y[-1]:
        return LCS(X[:-1], Y[:-1]) + X[-1]

    elif X[-1] != Y[-1]:
        return max(LCS(X[:-1], Y), LCS(X, Y[:-1]))


# --------------------------------------------------------------------------------------


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
