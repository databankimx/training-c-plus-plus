#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
    int a = 7;
    int b = 2;

    std::cout << "a + b = " << a + b << "\n";
    std::cout << "a - b = " << a - b << "\n";
    std::cout << "a * b = " << a * b << "\n";
    std::cout << "a / b = " << a / b << "\n";
    std::cout << "a % b = " << a % b << "\n";

    double c = 7.0;
    std::cout << "c / b = " << c / b << "\n";
    std::cout << "a / 2.0 = " << a / 2.0 << "\n";

    double average = static_cast<double>(a) / b;
    std::cout << "average = " << average << "\n";

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "average to two places = " << average << "\n";

    int count = 0;
    count++;
    count += 5;
    std::cout << "count = " << count << "\n";

    int total = 10;
    total -= 3;
    total *= 2;
    total /= 4;
    total %= 4;
    std::cout << "total = " << total << "\n";

    std::cout << "2 + 3 * 4 = " << 2 + 3 * 4 << "\n";
    std::cout << "(2 + 3) * 4 = " << (2 + 3) * 4 << "\n";
    std::cout << "10 - 4 - 3 = " << 10 - 4 - 3 << "\n";

    std::cout << "max(a, b) = " << std::max(a, b) << "\n";
    std::cout << "min(a, b) = " << std::min(a, b) << "\n";
    std::cout << "sqrt(16) = " << std::sqrt(16.0) << "\n";
    std::cout << "round(2.6) = " << std::round(2.6) << "\n";
    std::cout << "pow(2, 10) = " << std::pow(2.0, 10) << "\n";

    // Try: change b to 4. Predict a / b and a % b before you press Run.
    return 0;
}
