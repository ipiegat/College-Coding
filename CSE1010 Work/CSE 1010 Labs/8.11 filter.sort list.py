user_input = input()
string_list = user_input.split()
integer_list = []

for i in string_list:
    if int(i) >= 0:
        integer_list.append(int(i))

integer_list.sort()

for i in integer_list:
    print(i, end = ' ')