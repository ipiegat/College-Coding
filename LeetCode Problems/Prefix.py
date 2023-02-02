strs = ["flower","flow","flight"]

def prefix(strs):
    prefix = strs[0]
    for words in strs:
        if prefix[0] == words[0]:
            return prefix

print(prefix(strs))