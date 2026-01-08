#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

class MyClass {
    public:
        MyClass(): num(0), values() {}

        void randomNumber () {
            static bool seeded = false;
            if (!seeded) {
                std::srand(std::time(nullptr));
                seeded = true;
            }

            num = std::rand() % 100;
        }

        void checkVector () {
            if (std::find(values.begin(), values.end(), num) == values.end()) {
                values.push_back(num);
            }
        }

        const std::vector<int> getVector() const {
            return values;
        } 

    private:
        int num;
        std::vector<int> values;
};

int main() {
    MyClass a;

    for (int i = 0; i < 100; i++) {
        a.randomNumber();
        a.checkVector();
    }

    std::vector<int> v = a.getVector();
    std::sort(v.begin(), v.end());

    for (int x : v) {
        std::cout << x << " ";
    }
    
    std::cout << std::endl;


    return 0;
}