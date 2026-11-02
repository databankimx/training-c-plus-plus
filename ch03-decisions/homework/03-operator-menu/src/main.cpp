#include <iostream>

int main() {
    std::cout << "Enter an operator (+, -, *, /): " << std::flush;
    char op = ' ';
    std::cin >> op;

    std::cout << "Enter the first number: " << std::flush;
    double a = 0.0;
    std::cin >> a;

    std::cout << "Enter the second number: " << std::flush;
    double b = 0.0;
    std::cin >> b;

    switch (op) {
        case '+':
            std::cout << a + b << "\n";
            break;
        case '-':
            std::cout << a - b << "\n";
            break;
        case '*':
            std::cout << a * b << "\n";
            break;
        case '/':
            if (b == 0) {
                std::cout << "Cannot divide by zero.\n";
            } else {
                std::cout << a / b << "\n";
            }
            break;
        default:
            std::cout << "Unknown operator.\n";
            break;
    }

    return 0;
}
