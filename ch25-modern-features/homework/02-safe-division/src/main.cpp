#include <iostream>
#include <optional>

// Divides a by b. Returns nothing when b is zero, since the quotient doesn't exist.
std::optional<int> safeDivide(int a, int b) {
    if (b == 0) {
        return std::nullopt;
    }
    return a / b;
}

int main() {
    std::optional<int> first = safeDivide(10, 2);
    std::cout << "10 / 2 = ";
    if (first) {
        std::cout << first.value() << "\n";
    } else {
        std::cout << "no answer\n";
    }

    std::optional<int> second = safeDivide(1, 0);
    std::cout << "1 / 0 = ";
    if (second) {
        std::cout << second.value() << "\n";
    } else {
        std::cout << "no answer\n";
    }

    std::optional<int> third = safeDivide(9, 3);
    std::cout << "9 / 3 = ";
    if (third) {
        std::cout << third.value() << "\n";
    } else {
        std::cout << "no answer\n";
    }
    return 0;
}
