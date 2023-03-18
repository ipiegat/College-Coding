tuples1 = {(1, 2), (2, 3)}
tuples2 = {(2, 2), (2, 3)}

def solveable(x, y):
    # num_pawns = len(p_idxs)
    # possible_moves = valid_moves(k_idx)

    # # base case 1
    # if num_pawns == 0:
    #     return True
    # base case 2, if there is no move which the first move can take a pawn
    for i in x:
        for j in y:
            if i != j:
                return False
            

print(solveable(tuples1, tuples2))
