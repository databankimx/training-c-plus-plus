#include <iostream>

int main() {
    std::cout << "Break at 5:\n";
    int i = 0;
    while (true) {
        ++i;
        std::cout << i << "\n";
        if (i == 5) {
            break;
        }
    }

    std::cout << "Continue past 5:\n";
    for (int j = 1; j <= 10; ++j) {
        if (j <= 5) {
            continue;
        }
        std::cout << j << "\n";
    }

    // Try: change the break condition to i == 3. Predict how many lines print in the first loop.
    return 0;
}
