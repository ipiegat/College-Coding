strs = ["flower","flow","flight"]

def prefix(strs):
    minlen = len(strs[0])
    for w in strs:
        length = len(w)
        if minlen > length:
            minlen = length
        
    for i in range(minlen):
        c = strs[0][i]
        for w in strs:
            if c != w[i]:
                return strs[0][:i]
    return strs[0][:minlen]


print(prefix(strs))
        

        
    
    
