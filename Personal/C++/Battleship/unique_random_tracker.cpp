#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

class NumberTracker {
    public:
        NumberTracker(): current(0), values() {}

        void generate() {
            static bool seeded = false;
            if (!seeded) {
                std::srand(std::time(nullptr));
                seeded = true;
            }
            current = std::rand();
        }
    
        bool addIfUnique() {
            if (std::find(values.begin(), values.end(), current) == values.end()) {
                values.push_back(current);
                return true;
            }

            return false;
        }

        void sortValues() {
            std::sort(values.begin(), values.end());
        }

        const std::vector<int>& getValues() const {
            return values;
        }

        void printValues(const std::vector<int>& v) {
            for (int i : v) {
                cout << i << " ";
            }

            cout << endl;
        }

    private:
        int current;
        std::vector<int> values;
};

int main() {
    NumberTracker t;

    for (int i = 0; i < 100; i++) {
        t.generate();
        t.addIfUnique();
    }

    t.sortValues();
    t.printValues(t.getValues());
}
