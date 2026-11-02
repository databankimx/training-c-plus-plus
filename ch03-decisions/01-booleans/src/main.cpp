#include <iostream>

int main() {
    bool is_coding_fun = true;
    bool is_fish_tasty = false;

    std::cout << "Without boolalpha:\n";
    std::cout << "is_coding_fun: " << is_coding_fun << "\n";
    std::cout << "is_fish_tasty: " << is_fish_tasty << "\n";

    std::cout << std::boolalpha;
    std::cout << "With boolalpha:\n";
    std::cout << "is_coding_fun: " << is_coding_fun << "\n";
    std::cout << "is_fish_tasty: " << is_fish_tasty << "\n";

    int x = 10;
    int y = 9;
    std::cout << "x = " << x << ", y = " << y << "\n";
    std::cout << "x == 10: " << (x == 10) << "\n";
    std::cout << "x == y: " << (x == y) << "\n";
    std::cout << "x != y: " << (x != y) << "\n";
    std::cout << "x > y: " << (x > y) << "\n";
    std::cout << "x < y: " << (x < y) << "\n";
    std::cout << "x >= 10: " << (x >= 10) << "\n";
    std::cout << "y <= 8: " << (y <= 8) << "\n";

    // Try: change y to 10. Predict the value of x == y before you press Run.
    return 0;
}
