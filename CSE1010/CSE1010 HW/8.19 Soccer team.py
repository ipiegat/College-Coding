def read_item(player_number):
    a = input()
    if a == 'q':
        return None
    else:
        print(f"Enter player {player_number}'s jersey number:")
    
    b = input(f"Enter player {player_number}'s rating:\n\n")
    
    return int(a), int(b)

def create_roster():
    roster = {}
    player_number = 1
    pair = read_item(player_number)
    while pair is not None:
        player_number += 1
        roster[pair[0]] = pair[1]
        if player_number == 6:
            break
        pair = read_item(player_number)

    
    return roster
    
def Output_roster(roster):
    print("ROSTER")
    for key in sorted(list(roster.keys())):
        print(f"Jersey number: {key}, Rating: {roster[key]}")

def append_player(roster):
    jersey_number = int(input())
    rating = int(input())
    roster[jersey_number] = rating
    
    return roster

def remove_player(roster):
    jersey_number = int(input())
    roster.pop(jersey_number)
    return roster

def Update_player_rating(roster):
    jersey_number = int(input())
    new_rating = int(input())
    roster[jersey_number] = new_rating
    
    return roster

def Output_players_above_a_rating(roster):
    rating_limit = int(input())
    print("ABOVE", rating_limit)
    for i in sorted(list(roster.keys())):
        if roster[i] > rating_limit:
            print(f"Jersey number: {i}, Rating: {roster[i]}")
    
    return roster

def print_menu():
    print("\nMENU")
    print("a - Add player")
    print("d - Remove player")
    print("u - Update player rating")
    print("r - Output players above a rating")
    print("o - Output roster")
    print("q - Quit\n")

    print("Choose an option:")

def process_input(roster, character):
    if character == "a":
        new_roster = append_player(roster)
        return new_roster
    if character == "d":
        new_roster = remove_player(roster)
        return new_roster
    if character == "u":
        new_roster = Update_player_rating(roster)
        return new_roster
    if character == "r":
        new_roster = Output_players_above_a_rating(roster)
        return new_roster
    if character == "o":
        new_roster = Output_roster(roster)
        return new_roster
        

if __name__ == "__main__":
    roster = create_roster()
    Output_roster(roster)
    print_menu()
    character = input()
    while character != "q":
        new_roster = process_input(roster, character)
        print_menu()
        character = input()
        roster = new_roster