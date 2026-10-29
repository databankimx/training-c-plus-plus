#include <iostream>

int main() {
    std::cout << "Counting up:\n";
    for (int i = 0; i < 5; ++i) {
        std::cout << i + 1 << "\n";
    }

    std::cout << "Counting by twos:\n";
    for (int i = 0; i < 10; i += 2) {
        std::cout << i + 2 << "\n";
    }

    std::cout << "Counting down:\n";
    for (int i = 5; i > 0; i--) {
        std::cout << i << "\n";
    }

    std::cout << "Nested:\n";
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << i << ", " << j << "\n";
        }
    }

    // Try: change the counting-by-twos step to 3. Predict the numbers before you press Run.
    return 0;
}
