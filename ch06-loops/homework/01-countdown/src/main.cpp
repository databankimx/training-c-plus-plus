#include <iostream>

int main() {
    std::cout << "Enter a starting number: " << std::flush;
    int start = 0;
    std::cin >> start;

    for (int i = start; i > 0; --i) {
        std::cout << i << "\n";
    }
    std::cout << "Liftoff!\n";

    return 0;
}
