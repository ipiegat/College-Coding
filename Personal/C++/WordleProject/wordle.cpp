// Generate a 5 letter word that is unknown to player
// Player gets 6 guesses to guess the word
// If player guesses a letter in the word in the right spot, return green. Correct letter in wrong spot, return yellow. Incorrect return gray
// If correct early, end game. Let player know bang bang.

#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>

using namespace std;

class Wordle {
    public:
        const static int GRID_SIZE_X = 5;
        const static int GRID_SIZE_Y = 6;

        const string YELLOW_BG = "\033[33m";
        const string GRAY_BG   = "\033[90m";  // bright black = gray
        const string GREEN_BG  = "\033[32m";
        const string WHITE_BG  = "\033[97m";
        const string RESET  = "\033[0m";

        enum letter_state {
            GRAY,
            YELLOW,
            GREEN
        };

        Wordle(): guess_grid(GRID_SIZE_Y, vector<letter_state>(GRID_SIZE_X, letter_state::GRAY)), previous_guesses(6, string(5, '_')), guesses_attempted(0), wordle_answer(), guessed_word(), player_won(false), player_quit(false), alphabet("a b c d e f g h i j k l m n o p q r s t u v w x y z ") 
        {
            for (char c = 'a'; c <= 'z'; ++c) {
                letter_colors[c] = WHITE_BG;   // initialize as white
            }
        }

        // print instructions (occurs each turn)
        void initilization() {
            cout << "\nWELCOME TO WORDLE!" << endl;
            cout << "\n" << GREEN_BG << "GREEN MEANS CORRECT LETTER, CORRECT POSITION" << RESET << endl;
            cout << "\n" << YELLOW_BG << "YELLOW MEANS CORRECT LETTER, INCORRECT POSITION" << RESET << endl;
            cout << "\n" << GRAY_BG << "GRAY MEANS WORD DOES NOT CONTAIN LETTER, OR WORD HOLDS NO ADDITIONAL COPIES" << RESET << endl;
            cout << "\n" << "YOU GET 6 GUESSES! TYPE 'QUIT' IF YOU WANT TO END EARLY" << endl;
        }

        // function to create random 5-letter word
        void generate_word() {
            
            // open file and check if opened properly
            ifstream file("words.txt");
            if (!file) {
                cout << "Failed to open word file" << endl;
                return;
            }

            vector<string> words;
            string line;
            
            // iterate through file. record num of words and place words in vector. 
            while (getline(file, line)) {
                words.push_back(line);
            }

            // seed random number generator
            static bool seeded = false;
            if (!seeded) {
                srand(time(nullptr));
                seeded = true;
            }

            // make sure rand_num is within num of total words
            int rand_num = rand() % words.size();
            
            // set random word
            wordle_answer = words[rand_num];
        }
        
        // function to take in a word
        void player_guess() {
            while (true) {
                cout << "\n-------------------------\n";
                cout << "\nInput 5-letter word: ";
                cin >> guessed_word;

                if (guessed_word == "QUIT") {
                    player_quit = true;
                    return;
                }

                bool len_ok = (guessed_word.size() == 5);
                bool word_ok = len_ok && is_valid_word(guessed_word);

                if (len_ok && word_ok) return;

                print_guess_grid();
                print_alphabet();

                if (!len_ok) cout << "\nInvalid number of characters.\n";
                else cout << "\n" << guessed_word << " is not a valid word.\n";
            }
        }

        bool is_valid_word(const string& word) {
            // open file and check if opened properly
            ifstream file("words.txt");
            string line;

            while (file >> line) {
                if (line == word) {
                    return true;
                }
            }

            return false;
        }
        
        // changes character color in remaining colors list
        // yellow takes priority over gray, green takes priority over all colors
        void change_character_color(const char guess_letter, const string& color) {
            
            // if color is already green, don't overwrite
            if (letter_colors[guess_letter] == GREEN_BG) return;
            
            // if color is already yellow, only overwrite if it becomes green. Else, move on
            if (letter_colors[guess_letter] == YELLOW_BG) {
                if (color == GREEN_BG) {
                    letter_colors[guess_letter] = GREEN_BG; 
                    return;
                } else return;
            }

            // if gray, always overwrite 
            letter_colors[guess_letter] = color;
        }
        
        // function to determine green/yellow/gray,
        // to store the player guess in previous_guesses,
        // and to evaluate when the game STOPS (win or loss)
        // returns false if game should continue, true if game is finished
        bool game_loop() {
            // if letter is green, only make same letter yellow for remaining copies
            if (player_quit) {
                return true;
            }

            if (guesses_attempted >= GRID_SIZE_Y) {
                player_won = false;
                return true;
            }

            player_won = true;

            unordered_map<char, int> letter_counts;

            // keep track of copies of same letter <char letter, int copies>
            for (char c : wordle_answer) {
                letter_counts[c]++;
            }

            // CHECK FOR GREENS
            for (int i = 0; i < GRID_SIZE_X; i++) {
                if (guessed_word[i] == wordle_answer[i]) {
                    guess_grid[guesses_attempted][i] = letter_state::GREEN;
                    letter_counts[wordle_answer[i]]--;
                    change_character_color(guessed_word[i], GREEN_BG);
                }
            }

            // CHECK FOR YELLOWS AND GRAYS
            for (int i = 0; i < GRID_SIZE_X; i++) {
                // Don't mark a letter as yellow if it's already green 
                if (guess_grid[guesses_attempted][i] == letter_state::GREEN) continue;
                
                // If letter in wordle answer, mark yellow. If not, mark gray
                // ONLY mark yellow if copies > 0
                if ((wordle_answer.find(guessed_word[i]) != string::npos) && (letter_counts[guessed_word[i]] > 0)) {
                    guess_grid[guesses_attempted][i] = letter_state::YELLOW;
                    letter_counts[wordle_answer[i]]--;
                    change_character_color(guessed_word[i], YELLOW_BG);
                    player_won = false;
                } else {
                    guess_grid[guesses_attempted][i] = letter_state::GRAY;
                    change_character_color(guessed_word[i], GRAY_BG);
                    player_won = false;
                }
            }
            

            
            previous_guesses[guesses_attempted] = guessed_word;
            guesses_attempted++;
            
            // CHECK IF ALL GREENS
            if (guessed_word == wordle_answer) {player_won = true; return player_won;}
            if (guesses_attempted >= GRID_SIZE_Y) return true; // out of attempts -> stop
            return false;
        }

        // print letters not yet guessed by player
        void print_alphabet() {
  
            // print alphabet

            cout << "\nAlphabet: ";

            for (auto& pair : letter_colors) {
                cout << pair.second << pair.first << RESET << " ";
            }

            cout << endl;
        }

        // guess grid includes guessed letter location and state. Like "🟩S".
        void print_guess_grid() {

            cout << "Guesses remaining: " << 6 - guesses_attempted << "\n" << endl;
            int row = 0;
            int column = 0;
            for (const auto& word : guess_grid) {
                for (const auto& letter_state : word) {
                    switch(letter_state) {
                        case letter_state::GREEN: cout << GREEN_BG << previous_guesses[row][column] << RESET << " "; break;
                        case letter_state::YELLOW: cout << YELLOW_BG << previous_guesses[row][column] << RESET << " "; break;
                        case letter_state::GRAY: cout << GRAY_BG << previous_guesses[row][column] << RESET << " "; break;
                    }
                    column += 1;
                }

                row += 1;
                column = 0;

                cout << endl;
            }

        }

        // function to end game (win/lose)
        void end_game() {
            
            if (player_quit) {
                cout << "\nYou quit after " << guesses_attempted << " attempt(s)! Correct word was: " << wordle_answer << "\n" << endl;
            } else {
                if (player_won) {
                    cout << "\nYou win with " << guesses_attempted << " attempt(s)! Correct word was: " << wordle_answer <<  "\n" << endl;
                } else {
                    cout << "\nYou lose with " << guesses_attempted << " attempt(s)! Correct word was: " << wordle_answer << "\n" << endl;
                }
            }
        }
        
    private:
        vector<vector<letter_state>> guess_grid;
        vector<string> previous_guesses;
        unsigned int guesses_attempted;
        string wordle_answer;
        string guessed_word;
        bool player_won;
        bool player_quit;
        string alphabet;
        map<char, string> letter_colors;
};

int main() {
    Wordle game = Wordle();

    game.initilization();
    
    game.generate_word();
    game.player_guess();

    while (!game.game_loop()) {
        game.print_guess_grid();
        game.print_alphabet();
        game.player_guess();
    }

    game.print_guess_grid();
    game.end_game();
}