#include <iomanip>
#include <iostream>

double rectangleArea(double width, double height) {
    return width * height;
}

double circleArea(double radius) {
    const double pi = 3.14159;
    return pi * radius * radius;
}

int main() {
    std::cout << "Enter the width: " << std::flush;
    double width = 0.0;
    std::cin >> width;

    std::cout << "Enter the height: " << std::flush;
    double height = 0.0;
    std::cin >> height;

    std::cout << "Enter the radius: " << std::flush;
    double radius = 0.0;
    std::cin >> radius;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Rectangle area: " << rectangleArea(width, height) << "\n";
    std::cout << "Circle area: " << circleArea(radius) << "\n";

    return 0;
}
