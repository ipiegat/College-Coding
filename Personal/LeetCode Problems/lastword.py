# class Solution:
#     def lengthOfLastWord(self, s: str) -> int:
        
input_string = "Hello, this is an example butters"

# Split the string into words
words = input_string.split()

# Check if the list of words is not empty
if words:
    # Get the last word and calculate its length
    last_word = words[-1]
    length_of_last_word = len(last_word)
    print(f"The length of the last word is: {length_of_last_word}")
else:
    print("The input string does not contain any words.")
        