integer_list = []
n = 10

for i in range(1, 1+n):
        integer_list.append(i)

for i in integer_list:
    for j in integer_list:
        if i > j and i % j != 0:
            print(i)

    


    


