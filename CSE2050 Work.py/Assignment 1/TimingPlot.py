def bubble_sort(L):
    n = len(L) # no. of items in list
    for i in range(n): # for every item
        for j in range(n): # compare to every other item
            if L[i] < L[j]: # if out of order:
                L[i], L[j] = L[j], L[i] # swap items
L = [1, 5, 4]
print(L) # expect: [1, 5, 4]
bubble_sort(L)
print(L) # expect: [1, 4, 5]