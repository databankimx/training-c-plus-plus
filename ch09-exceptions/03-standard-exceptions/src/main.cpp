#include <iostream>
#include <stdexcept>

// Divides two numbers. A zero divisor throws a standard exception that describes the problem.
int safeDivide(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("the divisor must not be zero");
    }
    return a / b;
}

int main() {
    try {
        int first = safeDivide(10, 2);
        std::cout << "10 / 2 = " << first << "\n";

        int second = safeDivide(10, 0);
        std::cout << "10 / 0 = " << second << "\n";
    } catch (const std::exception& error) {
        std::cout << "Error: " << error.what() << "\n";
    }

    // Try: change the catch to catch (...), and predict what it can print. Then change it back.
    return 0;
}
