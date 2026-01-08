height = int(input())
width = int(input())
arrow_width = int(input())

while arrow_width <= width:
    arrow_width = int(input())

print(('*' * width + "\n") * height, end='')

for i in reversed(range(arrow_width)):
    print(('*')*(i+1))