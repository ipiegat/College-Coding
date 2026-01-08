words = str(input()).split(" ")

def tolower(words):
    lowercase = words.lower()
    return lowercase

lower_case = list(map(tolower, words))

for word, owo in zip(lower_case, words):
    count = lower_case.count(word)
    print(owo, count)