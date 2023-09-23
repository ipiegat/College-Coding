integers = map(int, input().split(" "))
lower, higher = map(int, input().split(" "))

for i in integers:
    if i <= higher and i >= lower:
        print(i, end=' ')