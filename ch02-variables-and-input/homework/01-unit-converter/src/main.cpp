#include <iostream>

int main() {
    std::cout << "Enter a temperature in Celsius: " << std::flush;

    double celsius = 0.0;
    std::cin >> celsius;

    const double fahrenheit = celsius * 9.0 / 5.0 + 32.0;
    std::cout << celsius << " C is " << fahrenheit << " F\n";

    return 0;
}
