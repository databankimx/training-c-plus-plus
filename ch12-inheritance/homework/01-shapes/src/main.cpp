#include <iomanip>
#include <iostream>

class Shape {
public:
    virtual double area() const {
        return 0.0;
    }
};

class Rectangle : public Shape {
public:
    double width = 0.0;
    double height = 0.0;

    Rectangle(double w, double h) {
        width = w;
        height = h;
    }

    double area() const override {
        return width * height;
    }
};

class Circle : public Shape {
public:
    double radius = 0.0;

    Circle(double r) {
        radius = r;
    }

    double area() const override {
        const double pi = 3.14159;
        return pi * radius * radius;
    }
};

void printArea(const Shape& shape) {
    std::cout << "Area: " << shape.area() << "\n";
}

int main() {
    std::cout << std::fixed << std::setprecision(2);

    Rectangle rect(3.0, 2.0);
    Circle circ(1.0);
    Shape plain;

    printArea(rect);
    printArea(circ);
    printArea(plain);

    return 0;
}
