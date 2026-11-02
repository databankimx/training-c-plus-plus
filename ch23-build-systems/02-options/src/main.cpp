#include <iostream>

#include "greeting.h"

int main() {
    std::cout << makeGreeting("Scott") << "\n";
    std::cout << makeGreeting("Ada") << "\n";

    // Try: change the default of USE_LOUD in CMakeLists.txt to ON, and predict the output before you press Run.
    return 0;
}
