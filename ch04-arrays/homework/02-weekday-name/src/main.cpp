#include <iostream>
#include <string>

int main() {
    std::string days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    std::cout << "Enter a day number (1-7): " << std::flush;
    int number = 0;
    std::cin >> number;

    if (number < 1 || number > 7) {
        std::cout << "That isn't a valid day number.\n";
        return 0;
    }

    std::cout << "Day " << number << " is " << days[number - 1] << "\n";
    return 0;
}
