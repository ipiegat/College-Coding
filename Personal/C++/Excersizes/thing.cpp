#include <iostream>
#include <memory>
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
        // delete copy constructor
        Singleton(const Singleton&) = delete;
        // delete move constructor
        Singleton(Singleton&&) = delete;
        // delete copy assignment operator
        Singleton& operator = (const Singleton&) = delete;
        // delete move assignment operator
        Singleton& operator = (Singleton&&) = delete;


        static Singleton& GetInstance() {
            static Singleton instance;
            return instance;
        }

    private:
        // default constructor
        // make private such that only one instance can be created at a time
        Singleton() = default;

};


template <typename T>
T add(T x, T y) {
    return x + y;
}

class Shape {
    public:
        virtual void draw() const {
            cout << "Drawing generic shape:" << endl;
        }

        virtual ~Shape() = default;

};

class Square : public Shape {
    public:
        void draw() const override {
            cout << "Drawing square" << endl;
        }
};

class Triangle : public Shape {
    public:
        void draw() const override {
            cout << "Drawing triangle" << endl;
        }
};

int main() {
    Singleton& a = Singleton::GetInstance();

    cout << "Ints: " << add(1, 2) << endl;
    cout << "Doubles: " << add(1.2, 1.3) << endl;

    unique_ptr<Shape> shape1 = make_unique<Square>();
    unique_ptr<Shape> shape2 = make_unique<Triangle>();
    
    Shape test;

    test.draw();
    shape1->draw();
    shape2->draw();
    
}

