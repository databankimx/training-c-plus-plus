#include <iostream>

int main() {
    std::cout << "Enter a year: " << std::flush;
    int year = 0;
    std::cin >> year;

    bool leap = (year % 4 == 0) && (year % 100 != 0 || year % 400 == 0);

    if (leap) {
        std::cout << year << " is a leap year.\n";
    } else {
        std::cout << year << " is not a leap year.\n";
    }

    return 0;
}
