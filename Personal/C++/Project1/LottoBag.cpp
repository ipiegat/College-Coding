#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

class LottoBag {
    /** This is a class **/
    public:
        LottoBag(): bag(100), drawn() {
            for (int i = 0; i < 100; i++) {
                bag[i] = i;
            }
        }
        
        bool drawOne(int& out) {
            if (bag.size() == 0) {
                return false;
            }
            
            static bool seeded = false;
            if (!seeded) {
                std::srand(std::time(nullptr));
                seeded = true;
            }
            
            int random = std::rand() % bag.size();
            out = bag[random];
            bag[random] = bag.back();
            bag.pop_back();
            drawn.push_back(out);
            return true;
        }

        vector<int> drawMany(int k) {
            vector<int> toReturn = vector<int>(); // RAII
            int x = 0;
            for (int i = 0; i < k; i++) {
                if (!drawOne(x)) {
                    break;
                }
                toReturn.push_back(x);
            }
            return toReturn;
        }

        void reset() {
            bag.clear();            // Clear the bag
            bag.resize(100);        // Make space for 100 elements
            for (int i = 0; i < 100; i++) {
                bag[i] = i;
            }
            // std::iota(bag.begin(), bag.end(), 0);  // Fill with 0-99
            drawn.clear(); 
        }

        const vector<int>& remaining() const {
            return bag;
        }

        const vector<int>& history() const {
            return drawn;
        }
    private:
        vector<int> bag;
        vector<int> drawn;
};

int main() {
    LottoBag b;

    int x;
    while (b.drawOne(x)) {
        std::cout << x << " ";
    }
    std::cout << "\nRemaining: " << b.remaining().size() << "\n";

    b.reset();

    auto v = b.drawMany(10);
    std::sort(v.begin(), v.end());
    for (int n : v) std::cout << n << " ";
    std::cout << "\nHistory size: " << b.history().size() << "\n";
}
