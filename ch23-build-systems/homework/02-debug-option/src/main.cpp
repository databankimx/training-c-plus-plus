#include <iostream>

int main() {
    int total = 0;
    for (int number = 1; number <= 4; number++) {
        total += number;
#ifdef SHOW_STEPS_ON
        std::cout << "Adding " << number << ": total " << total << "\n";
#endif
    }

    std::cout << "Sum: " << total << "\n";
    return 0;
}
