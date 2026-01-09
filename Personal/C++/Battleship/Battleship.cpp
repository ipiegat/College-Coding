#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

const static int BOARD_SIZE = 9;

enum location_state {
    EMPTY = 0,
    SHIP = 1,
    HIT = 2,
    MISS = 3
}

class GameManager {
    public:
        GameManager(): player_board(BOARD_SIZE, vector<location_state>(BOARD_SIZE, location_state::EMPTY)), 
                       enemy_board(BOARD_SIZE, vector<location_state>(BOARD_SIZE, location_state::EMPTY)) {}


        bool intake_move() {
            /* Processes move if valid. Returns false if player wants to quit. */
            int x = 0;
            int y = 0;
            bool valid = false;
            
            char c = " ";
            cout << "Enter q to quit, anything else to continue: ";
            cin >> x;
            if(x == "q") {
                return false;
            }

            do {
                x = get_int_from_user("GIVE ME AIM X: ");
                y = get_int_from_user("GIVE ME AIM Y: ");
            } while (!handle_guess(x, y, enemy_board));

            make_enemy_move();
        }

        void make_enemy_move() {
            // guess randomly until valid
            do {
                x = rand() % BOARD_SIZE;
                y = rand() % BOARD_SIZE;
            } while (!handle_guess(x, y, player_board));
        }

        bool handle_guess(int x, int y, vector<vector<location_state>>& board) {
            /*
            return false is invalid guess (empty)
            return true if valid
            */
            switch board[x][y]:
                case location_state.EMPTY:
                    board[x][y] = location_state.MISS;
                    break;
                case location_state.SHIP:
                    board[x][y] = location_state.HIT
                    break;
                case location_state.HIT:
                case location_state.MISS:
                    return false;
            
            return true;
        }

        void show_boards() {
            // go through player board
            // print X on hits, S for ships, O for empty, M for miss
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    switch player_board[i][j]:
                        case location_state.EMPTY:
                            cout << "O" << " ";
                            break;
                            
                        case location_state.SHIP:
                            cout << "S" << " ";
                            break;
                            
                        case location_state.HIT:
                            cout << "X" << " ";
                            break;
                        
                        case location_state.MISS:
                            cout << "M" << " ";
                            break;
                }
                cout << endl;
            }

            cout << endl;

            // show enemy board
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    switch enemy_board[i][j]:
                        case location_state.EMPTY:
                            cout << "O" << " ";
                            break;
                            
                        case location_state.SHIP:
                            cout << "O" << " ";
                            break;
                            
                        case location_state.HIT:
                            cout << "X" << " ";
                            break;
                        
                        case location_state.MISS:
                            cout << "M" << " ";
                            break;
                }
                cout << endl;
            }
        }

        bool try_place_ship(int x, int y, vector<vector<location_state>>& board) {
            int ship_size = 5;

            // validate loc is in board
            if (x < 0 || x >= BOARD_SIZE - ship_size) {
                return false;
            }
            if (y < 0 || y >= BOARD_SIZE - ship_size) {
                return false;
            }

            // validate no overlap
            for(int i = 0; i < ship_size; i++) {
                if(board[x + i][y] != location_state.EMPTY) {
                    return false;
                }
            }
            
            // place ship
            for(int i = 0; i < ship_size; i++) {
                board[x + i][y] = location_state.EMPTY;
            }
            return true
        }

        int get_int_from_user(str msg) {
            // Includes input validation
            cout << msg;
            int x = 0;
            cin >> x;
            
            while (x < 0 || x >= BOARD_SIZE) {
                cout >> "Must be in range [0, " << BOARD_SIZE - 1 << "]: ";
                cin >> x;
            }

            return x;
        }

        void handle_setup() {
            // Set up player board
            int x = 0;
            int y = 0;
            int num_ships_placed = 0;
            while (num_ships_placed < 3) {
                x = get_int_from_user("GIVE ME X: ");
                y = get_int_from_user("GIVE ME Y: ");
                if (!try_place_ship(x, y, player_board)) {
                    cout << "FAIL\n";
                }
                else {
                    num_ships_placed++;
                }
            }

            // set up enemy board
            for (int i = 0; i < 3; i++) {
                static bool seeded = false;
                if (!seeded) {
                    srand(time(nullptr));
                    seeded = true;
                }
            
                x = rand() % BOARD_SIZE;
                y = rand() % BOARD_SIZE;
                if (!try_place_ship(x, y, enemy_board)) {
                    cout << "FAIL FAIL FAIL\n";
                }
                else {
                    num_ships_placed++;
                }
            }
        }

        void show_instructions() {
            cout << "WELCOME TO BATTLESHIP\n";
            cout << "PLACE YOUR THREE SHIPS\n";
        }

        void exit_msg() {
            cout << "BYE\n";
        }
    private:
        vector<vector<location_state>> player_board;
        vector<vector<location_state>> enemy_board;
};



void main() {
    GameManager g = GameManager();

    g.show_instructions();

    g.handle_setup(); // is interactive
    
    do { // main game loop
        g.show_boards();
    } while(g.intake_move())
    
    g.exit_msg();
}