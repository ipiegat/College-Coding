input_str = str(input())
print("Enter a sentence or phrase:")
print("\nYou entered:", input_str)


def get_num_of_characters(input_str):
    isChar = 0
    for char in input_str:
        isChar += 1
    return isChar
    
def output_without_whitespace(input_str):
    return input_str.replace(" ", "")

if __name__ == '__main__':
    print("\nNumber of characters:", get_num_of_characters(input_str))
    print("String with no whitespace:", output_without_whitespace(input_str))