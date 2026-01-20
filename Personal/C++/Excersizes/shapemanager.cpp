#include <iostream>
#include <memory>
#include <string>

namespace shape_area {
    template <typename T>
    T rectangle(T width, T height) {
        return width * height;
    }

    template <typename T>
    T circle(T radius) {
        T pi = static_cast<T>(3.141592653589793);
        return pi * radius * radius;
    }
}

class Shape {
public:

    virtual double double_area() const = 0;
    virtual std::string show_name() const = 0;
    virtual ~Shape() = default;

};

class Rectangle : public Shape {
public:
    Rectangle(double w, double h): width(w), height(h) {}
    
    double double_area() const override {
        return shape_area::rectangle(width, height);
    }

    std::string show_name() const override {
        return "Area of Rectangle: ";
    }

private:
    double width;
    double height;
};

class Circle : public Shape {
public:
    Circle(double r): radius(r) {}

    double double_area() const override {
        return shape_area::circle(radius);
    }

    std::string show_name() const override {
        return "Area of Circle: ";
    }

private:
    double radius;
};

int main() {
    double radius = 0;
    double width = 0;
    double height = 0;

    std::cout << "Input radius: ";
    std::cin >> radius;
    std::cout << "Input width: ";
    std::cin >> width;
    std::cout << "Input height: ";
    std::cin >> height;

    std::unique_ptr<Shape> shape1 = std::make_unique<Circle>(radius);
    std::unique_ptr<Shape> shape2 = std::make_unique<Rectangle>(width, height);

    std::string name1 = shape1->show_name();
    double area1 = shape1->double_area();

    std::string name2 = shape2->show_name();
    double area2 = shape2->double_area();

    std::cout << '\n' << name1 << area1 << std::endl;
    std::cout << name2 << area2 << std::endl;

}