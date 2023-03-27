# Create a board

def solve_puzzle(L, visited_moves = None, visible_moves = None):
    # if the search is just starting
    if visited_moves is None: 
        visited_moves = set()
        visible_moves = {0} # initialize empty set and first element as start
    
    # going through the set of visibile indices 
    for n in visible_moves:
        # if n is the last item in the list
        if n == len(L) - 1:
            # board is solveable
            return True

        # add used CW and CCW moves to visible set
        new_visible_moves = {(n + L[n]) % len(L), (n - L[n]) % len(L)}
        # recursively call solve_puzzle and pass in the list, the visited index/indeces, and remove looked at indeces
        if solve_puzzle(L, visited_moves | {n}, (visible_moves - {n}) | (new_visible_moves - visited_moves)):
            return True
    
    return False

    



    

