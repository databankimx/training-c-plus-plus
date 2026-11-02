#include <iostream>
#include <string>

int main() {
    std::string food = "Pizza";
    std::string& meal = food;   // meal is another name for food

    std::cout << food << "\n";
    std::cout << meal << "\n";

    meal = "Tacos";
    std::cout << food << "\n";

    // Try: add a second reference to food, called dinner. Change dinner, and predict what food and meal show.
    return 0;
}
