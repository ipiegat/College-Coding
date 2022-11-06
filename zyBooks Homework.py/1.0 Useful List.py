# range(start value, end value, step)
# if, elif, else
# and
# def function(arguement) / argument = passing input/value
# float(non-integer)
# string()
string = "abcd"
print(string[::-1])

st = "abc"
def reverse(st):
    result = ''
    for i in range(len(st)):
        result = st[i] + result
    return result
print(reverse(st))

n = int(input(3))
def power(n):
    if i in range(n-1):
        a = print(3**(i-1), ",", end='')
    return a

def Triangle(n):
    for i in range():
        