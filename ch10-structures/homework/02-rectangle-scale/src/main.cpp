#include <iomanip>
#include <iostream>

struct Rectangle {
    double width = 1.0;
    double height = 1.0;
};

double area(Rectangle r) {
    return r.width * r.height;
}

void scale(Rectangle& r, double factor) {
    r.width *= factor;
    r.height *= factor;
}

int main() {
    std::cout << std::fixed << std::setprecision(2);

    Rectangle r{3.0, 2.0};
    std::cout << "Area: " << area(r) << "\n";

    scale(r, 2.0);
    std::cout << "Area: " << area(r) << "\n";

    return 0;
}
