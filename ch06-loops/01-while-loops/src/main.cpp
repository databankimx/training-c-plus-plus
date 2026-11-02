#include <iostream>

int main() {
    std::cout << "while loop:\n";
    int i = 0;
    while (i < 3) {
        std::cout << ++i << "\n";
    }

    std::cout << "do-while loop:\n";
    int j = 10;
    do {
        std::cout << "j is " << j << "\n";
        j++;
    } while (j < 10);

    // Try: change the do-while condition to j < 12. Predict how many lines print before you press Run.
    return 0;
}
