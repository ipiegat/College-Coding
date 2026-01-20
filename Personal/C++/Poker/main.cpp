/*  
game of poker vs. bots
player balance is valued in "big blinds". start with BB * 100
bots will play according to chance with variance such that they are not always predictable
give each participant 2 cards from deck (no duplicates)
initiate round of betting (little blind, big blind, button). initially start at random player
the action of each person is printed. can use grid to represent table in circular fascion with colors that represent last action
when it is players turn, and no bet is placed, player can either check or bet
when it is players turn, and a bet is placed, a player can either call or raise (raise must be at least 2x previous value)
raises and calls are immediately put in the pot and deducted from players bank. cannot be recovered
after initial turn (when every remaining player checks, or every active player calls (folding excuses player), or every remaining player folds), deal flop->turn->river
*/
#include <unordered_map>

enum class Suit {
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES
};

struct Card {
        int number;
        Suit suit;
};

class GameManager {
    public:
        GameManager(int num_bots_): num_bots(std::move(num_bots_)), deck(),  {}

        void initialize_game() {}
        
        void bot_turn() {}
        
        void player_turn () {}
        void shuffle_deck() {

            for (int s = 0; s < 4; ++s) {
                for (int r = 2; r <= 14; ++r) {
                    deck.push_back({r, static_cast<Suit>(s)});
                }
            }

        }
    private:
    
        bool at_lb;
        bool at_bb;
        bool at_button;
        const int little_blind;
        const int big_blind;
        const int num_bots;
        const int deck_size;
        std::vector<Card> deck;

        
        // each bot gets an unique number and stack. player is assigned num 0
        std::unordered_map<int, int> stacks;
};


void main() {

}

/*
Board: Ace Eight King
Bot 1, Bot 2, You, Bot 3, Bot 4
Bot 1 bets 20BB 


Board: Ace Eight King
Bot 1,       Bot 2,      You,        Bot 3,       Bot 4
Bets 20BB 


Round 1:

                                Board: Pre-flop
                                Pot: 20BB 

        LB           BB                   D                         
        Bot 1 ,       Bot 2 (2000BB),      You,        Bot 3,       Bot 4
        ----------------------------------------------------------------------
Turn 1 | Bet 20BB     Call 20BB            Call 20BB   Call 20BB    Raise 40BB
Turn 2 | Call 40BB    Fold                 Fold        Fold     

Round 2:
        Board: A K 8
        Pot: 
   |     LB           BB                                
   |     Bot 1,       Bot 4
Turn 1 | Check        Check

Round 3:
        Board: A K 8 9
        Pot: 
   |     LB           BB                                
   |     Bot 1,       Bot 4
Turn 1 | Check        Check
*/