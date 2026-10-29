#include <iostream>
#include <stdexcept>

int main() {
    while (true) {
        try {
            std::cout << "Enter your age (0-120): " << std::flush;
            int age = 0;
            if (!(std::cin >> age)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                throw std::invalid_argument("not a number");
            }
            if (age < 0 || age > 120) {
                throw std::out_of_range("age must be from 0 to 120");
            }
            std::cout << "Age accepted: " << age << "\n";
            break;
        } catch (const std::exception& error) {
            std::cout << error.what() << "\n";
        }
    }

    return 0;
}
