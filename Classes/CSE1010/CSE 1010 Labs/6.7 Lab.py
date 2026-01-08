x = int(input())


while(x > 0):
    print(f'{x % 2}', end = "")
    x = int(x // 2)
print()