#include <iostream>
#include <string>

int main() {
    int scores[] = {10, 20, 30, 40, 50};
    std::cout << "Scores:\n";
    for (int score : scores) {
        std::cout << score << "\n";
    }

    std::string colors[] = {"red", "green", "blue"};
    std::cout << "Colors:\n";
    for (std::string color : colors) {
        std::cout << color << "\n";
    }

    // Try: add "yellow" to the colors array. Predict whether the loop needs any other change.
    return 0;
}
