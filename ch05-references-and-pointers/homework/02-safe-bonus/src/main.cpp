#include <iostream>

void addBonus(int* score, int bonus) {
    if (score == nullptr) {
        std::cout << "No score to update.\n";
        return;
    }
    *score += bonus;
}

int main() {
    int points = 50;

    addBonus(&points, 10);
    std::cout << "Points: " << points << "\n";

    addBonus(nullptr, 5);
    std::cout << "Points: " << points << "\n";

    return 0;
}
