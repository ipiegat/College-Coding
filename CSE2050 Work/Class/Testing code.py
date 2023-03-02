X = "abcd"
Y = "bc"

def LCS(X, Y):
    if X == "" or Y == "":
        return ""
    
    elif X[-1] == Y[-1]:
        return LCS(X[:-1], Y[:-1]) + X[-1]
    
    elif X[-1] != Y[-1]:
        return max(LCS(X[:-1], Y), LCS(X, Y[:-1]))

print(LCS(X,Y))
