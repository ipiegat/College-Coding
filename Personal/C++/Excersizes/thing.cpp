#include <iostream>

using namespace std;

class RAII {
    public:
        RAII() {
            cout << "1" << endl;
        }

        ~RAII() {
            cout << "2" << endl;
        }

};

int main() {
    RAII a;
    cout << "3" << endl;
}