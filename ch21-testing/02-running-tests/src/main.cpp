#include <iostream>
#include <string>

// Limits value to the range from low to high. Values below low become low, and values above high become high.
int clamp(int value, int low, int high) {
    if (value < low) {
        return low;
    }
    if (value > high) {
        return high;
    }
    return value;
}

void check(bool passed, const std::string& name, int& failures) {
    if (passed) {
        std::cout << "PASS " << name << "\n";
    } else {
        std::cout << "FAIL " << name << "\n";
        failures++;
    }
}

int main() {
    int failures = 0;

    check(clamp(50, 0, 100) == 50, "inside the range stays the same", failures);
    check(clamp(-5, 0, 100) == 0, "below the range becomes the low end", failures);
    check(clamp(150, 0, 100) == 100, "above the range becomes the high end", failures);
    check(clamp(0, 0, 100) == 0, "the low end stays the same", failures);
    check(clamp(100, 0, 100) == 100, "the high end stays the same", failures);

    std::cout << "Failures: " << failures << "\n";

    // The exit code is the result of the program. Zero means every check passed, and CTest reads it.
    // Try: change the low end in the second check to 10, so it fails. Predict the exit code before you press Test.
    return failures == 0 ? 0 : 1;
}
