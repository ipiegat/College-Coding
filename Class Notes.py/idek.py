n = 5


def powersofthree(n):
    for i in range(n - 1):
        a = print(3**i, ",", end="")
    return a


powersofthree(n)
print()

a = 4


def triangle(a):
    for i in range(a, 1, -1):
        while a > 0:
            print(a)
            a = a - 1


triangle(a)
