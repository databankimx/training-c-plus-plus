#include "math.hpp"

#include <cstdlib>
#include <iostream>

int main() {
    int failures = 0;

    auto check = [&failures](bool passed, const char* description) {
        if (!passed) {
            std::cout << "FAILED: " << description << "\n";
            ++failures;
        }
    };

    check(add(2, 3) == 5, "2 + 3 is 5");
    check(add(-1, 1) == 0, "-1 + 1 is 0");
    check(add(0, 0) == 0, "0 + 0 is 0");

    if (failures == 0) {
        std::cout << "All tests passed\n";
    }
    return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
