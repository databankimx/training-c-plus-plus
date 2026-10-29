#include <iostream>
#include <string>

int main() {
    int number = 10;
    std::cout << number << "\n";

    number = 15;
    std::cout << number << "\n";

    double decimal = 5.99;
    std::cout << decimal << "\n";

    char letter = 'a';
    std::cout << letter << "\n";

    std::string text = "howdy";
    std::cout << text << "\n";

    bool flag = false;
    std::cout << flag << "\n\n";

    std::cout << "(" << number << ", " << decimal << ", " << letter << ", " << text << ", " << flag << ")\n";

    int other = 10;
    std::cout << number + other << "\n";

    int x = 5, y = 6, z = 50;
    std::cout << x + y + z << "\n";

    int first, second, third;
    first = second = third = 50;
    std::cout << first + second + third << "\n";

    const double pi = 3.14159;
    std::cout << "pi is about " << pi << "\n";

    float myFloat = 5.75f;
    std::cout << myFloat << "\n";

    double myDouble = 19.99;
    std::cout << myDouble << "\n";

    float bigFloat = 35e3f;
    double bigDouble = 12E4;
    std::cout << bigFloat << " " << bigDouble << "\n";

    char code = 97;
    std::cout << code << "\n";

    // Try: change pi to a new value, such as 3.0. What does the compiler say?
    return 0;
}
