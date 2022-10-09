user_text = str(input())

notChar = 0
isChar = 0
for char in user_text:
    if char.isalpha():
        isChar += 1
    if char == "?":
        isChar += 1
print(isChar)