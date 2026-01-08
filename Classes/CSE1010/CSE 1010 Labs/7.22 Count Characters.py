user_string = str(input())
first_character = user_string[0]
other_characters = user_string[1:]
count = other_characters.count(first_character)

if count != 1:
    print(count, first_character + "'s")
else:
    print(count, first_character)