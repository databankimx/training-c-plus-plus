#include <iomanip>
#include <iostream>

#include "Temperature.h"

int main() {
    std::cout << std::fixed << std::setprecision(2);

    std::cout << 0.0 << " C is " << celsiusToFahrenheit(0.0) << " F\n";
    std::cout << 100.0 << " C is " << celsiusToFahrenheit(100.0) << " F\n";
    std::cout << -40.0 << " C is " << celsiusToFahrenheit(-40.0) << " F\n";
    std::cout << 212.0 << " F is " << fahrenheitToCelsius(212.0) << " C\n";
    std::cout << 32.0 << " F is " << fahrenheitToCelsius(32.0) << " C\n";

    return 0;
}
