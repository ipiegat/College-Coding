num1 = int(input())
num2 = int(input())

if num2 < num1:
    print("Second integer can't be less than the first.")
else:
    output = range(num1, num2+1, 5)
    for i in output:
        print(i, '', end='')
    print()