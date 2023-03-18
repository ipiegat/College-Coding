# make completable chess board and non-completable chess board

# knight searches for spot in L pattern

# if there is a pawn there move there

# repeat until cannot find pawn in L pattern or until all pawns are gone

# 0 7
# 7
# 0


def valid_moves(k_idx: tuple):
    # valid moves starting clockwise from 12
    m1 = (k_idx[0] + 2, k_idx[1] + 1)
    m2 = (k_idx[0] + 1, k_idx[1] + 2)
    m3 = (k_idx[0] - 1, k_idx[1] + 2)
    m4 = (k_idx[0] - 2, k_idx[1] + 1)
    m5 = (k_idx[0] - 2, k_idx[1] - 1)
    m6 = (k_idx[0] - 1, k_idx[1] - 2)
    m7 = (k_idx[0] + 1, k_idx[1] - 2)
    m8 = (k_idx[0] + 2, k_idx[1] - 1)
    all_moves = {m1, m2, m3, m4, m5, m6, m7, m8}

    # create empty set
    possible_moves = set()

    # for each value in the pair
    for x, y in all_moves:
        # if both values are positive
        if x in range(0, 8) and y in range(0, 8):
            # create tuple
            value = (x, y)
            # add tuple to possible moves
            possible_moves.add(value)

    return possible_moves


def solveable(p_idxs, k_idx):
    num_pawns = len(p_idxs)
    possible_moves = valid_moves(k_idx)
    valid_set = possible_moves & p_idxs  # finding moves where horse can take pawn

    # if no pawns board is passable
    if num_pawns == 0:
        return True

    # if no valid moves remain not possible to solve
    elif len(valid_set) == 0:
        return False

    # move horse to pawns place and remove pawn
    for move in valid_set:
        # change horse position to pawn position
        knight_pos = move
        # remove taken pawn from set of pawns
        new_pawns = p_idxs - {knight_pos}
        # recursively call with new pawn and knight positions
        if solveable(new_pawns, knight_pos):
            return True

    return False


# print(valid_movess())
# print(solveable({(2, 3), (4, 4)}, (0, 4)))


# return True if no pawns left

# find all possible moves
# find all new board configs
# recursively call solve_board on all new configs
# if any are solved, return solution plus correct move
