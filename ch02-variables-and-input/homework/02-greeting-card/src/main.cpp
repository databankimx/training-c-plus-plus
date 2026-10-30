#include <iostream>
#include <string>

int main() {
    std::cout << "What is your name? " << std::flush;
    std::string name;
    std::getline(std::cin, name);

    std::cout << "How old are you? " << std::flush;
    int age = 0;
    std::cin >> age;

    std::cout << "Hello, " << name << ".\n";
    std::cout << "Next year you will be " << age + 1 << ".\n";

    return 0;
}
