string = str(input())

for i in string:
    if string[-2] != " ":
        print("Eating", string[-1] + string[-2], string[:-3], "a day keeps the doctor away.")
    
if string[-2] == " ":
    print("Eating", string[-1], string[:-2], "a day keeps the doctor away.")