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

class Singleton {
    public:
        // delete default constructor (don't delete, this is example)
        // Singleton() = delete;
        // delete copy constructor
        Singleton(const Singleton&) = delete;
        // delete move constructor
        Singleton(Singleton&&) = delete;
        // delete copy assignment operator
        Singleton& operator = (const Singleton&) = delete;
        // delete move assignment operator
        Singleton& operator = (Singleton&&) = delete;
        // delete destructor (don't do)
        // ~Singleton() = delete;


        static Singleton& GetInstance() {
            static Singleton instance;
            return instance;
        }

    private:
        // default constructor
        // make private such that only one instance can be created at a time
        Singleton() = default;

};

int main() {
    Singleton& a = Singleton::GetInstance();
}

