#include <iostream>

int main() {
    std::cout << "Enter a number: " << std::flush;
    int number = 0;
    std::cin >> number;

    for (int i = 1; i <= 10; ++i) {
        std::cout << number << " x " << i << " = " << number * i << "\n";
    }

    return 0;
}
