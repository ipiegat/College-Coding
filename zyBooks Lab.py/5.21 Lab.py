first_num = int(input())
list = []

for i in range(first_num):
    list.append(int(input()))

last_num = int(input())

for i in range(first_num):
    if list[i] <= last_num:
        list[i] = str(list[i])
        print(list[i] + ",", end='')