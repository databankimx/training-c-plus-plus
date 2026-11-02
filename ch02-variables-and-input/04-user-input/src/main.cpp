#include <iostream>
#include <string>

int main() {
    std::cout << "Enter some text: " << std::flush;
    std::string text;
    std::getline(std::cin, text);
    std::cout << "You entered: " << text << "\n";

    int x = 0;
    std::cout << "Enter a number: " << std::flush;
    std::cin >> x;
    std::cout << "You entered: " << x << "\n";

    int y = 0;
    std::cout << "Enter another number: " << std::flush;
    std::cin >> y;
    std::cout << "You entered: " << y << "\n";

    std::cout << x << " + " << y << " = " << x + y << "\n";

    // Try: type a word instead of a number at the second prompt. What does the program print for x?
    return 0;
}
