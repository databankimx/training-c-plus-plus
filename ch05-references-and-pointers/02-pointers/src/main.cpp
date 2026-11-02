#include <iostream>
#include <string>

int main() {
    std::string food = "Pizza";
    std::string* ptr = &food;   // ptr holds the address of food

    std::cout << food << "\n";
    std::cout << *ptr << "\n";

    *ptr = "Hamburger";
    std::cout << food << "\n";

    std::string* empty = nullptr;
    if (empty == nullptr) {
        std::cout << "The pointer is empty.\n";
    }

    // Try: change the value through ptr to "Salad", then predict what food shows.
    return 0;
}
