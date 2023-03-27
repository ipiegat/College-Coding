L = ([1, 3, 2], [4, 7, 6])

def insertionsort(L):
    n = len(L)
    for i in range(n):
        j = n - i - 1
        while j < n - 1 and L[j]>L[j+1]:
            L[j], L[j+1] = L[j+1], L[j]
            j+=1
    
    return L

print(insertionsort(L))