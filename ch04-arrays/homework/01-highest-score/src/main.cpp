#include <iostream>

int main() {
    int scores[3] = {0, 0, 0};

    std::cout << "Score 1: " << std::flush;
    std::cin >> scores[0];
    std::cout << "Score 2: " << std::flush;
    std::cin >> scores[1];
    std::cout << "Score 3: " << std::flush;
    std::cin >> scores[2];

    int highest = scores[0];
    if (scores[1] > highest) {
        highest = scores[1];
    }
    if (scores[2] > highest) {
        highest = scores[2];
    }

    std::cout << "The highest score is " << highest << "\n";
    return 0;
}
