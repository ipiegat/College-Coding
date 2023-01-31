"""
Coding Question 1
Create a python program that will determine if a given year is a leap year. Using nested if....else
statements, follow the guideline below to create your leap year program.
“A leap year is exactly divisible by 4 except for century years (years ending with 
00). The century year is a leap year only if it is perfectly divisible by 400. “
"""

year = int(input())

if year % 400 == 0:
    print(year, "is a leap year")
elif year % 4 == 0 and year % 100 != 0:
    print(year, "is a leap year")
else:
    print(year, "is not a leap year")

"""
Coding Question 2
Given an integer, create a program that will calculate the amount of digits in the integer. 
"""

integer = int(input())
integer = str(integer)
digit_count = len(integer)
print(digit_count)

# Complete