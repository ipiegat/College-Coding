highway_number = int(input())
serving = highway_number % 100
s1 = "I-" + str(highway_number)
s2 = "I-" + str(serving) + ", going"
r1 = highway_number % 2
r2 = serving % 100

if highway_number in range(1, 99) and r1 == 0 and r2 != 0:
    print(s1, "is primary, going east/west.")
elif highway_number in range(1, 99) and r1 != 0 and r2 != 0:
    print(s1, "is primary, going north/south.")
elif highway_number in range(100, 999) and r1 == 0 and r2 != 0:
    print(s1, "is auxiliary, serving", s2, "east/west.")
elif highway_number in range(100, 999) and r1 != 0 and r2 != 0:
    print(s1, "is auxiliary, serving", s2, "north/south.")
else:
    print(highway_number, "is not a valid interstate highway number.")
