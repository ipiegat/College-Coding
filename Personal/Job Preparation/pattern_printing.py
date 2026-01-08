# Goal: Use python to print multiple different patters of shapes

# Shape 1: Right-half pyramid

# *
# **
# ***
def right_half_pyramid(n):
    for i in range(1, n+1):
        print("*" * i)

#   *
#  **
# ***
def left_half_pyramid(n):
    for i in range(1,n+1): 
        print(('*' * i).rjust(n))

#   *
#  ***
# *****
def full_pyramid(n):
    # n = height
    offset = 2 * n
    for i in range(n):
        print(" " * (offset - 2*i) + "* "*(2*i + 1))

# For example, let's say we have the numbers 12 and 18. 
# The factors of 12 are 1, 2, 3, 4, 6, and 12. 
# The factors of 18 are 1, 2, 3, 6, 9, and 18. 
# The largest number that appears in both lists is 6. So, 6 is the GCD of 12 and 18.

def GCD(x, y):
    factors_x = []
    factors_y = []
    common_factors = []

    for i in range(1, x+1):
        if (x % i) == 0:
            factors_x.append(i)

    for i in range(1, y+1):
        if (y % i) == 0:
            factors_y.append(i)

    for i in factors_x:
        if i in factors_y:
            common_factors.append(i)
    
    return max(common_factors)

def diamond(n):

    for i in range(1,n+1): print(('*'*(2*i-1)).center(2*n-1))
    for i in range(n-1,0,-1): print(('*'*(2*i-1)).center(2*n-1))

if __name__ == "__main__":
    diamond(4)