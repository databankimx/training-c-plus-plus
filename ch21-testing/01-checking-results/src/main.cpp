#include <iostream>
#include <string>

// The function under test. It returns the sum of two numbers.
int add(int a, int b) {
    return a + b;
}

// Reports one check: PASS when the condition holds, FAIL when it doesn't. Each failure is counted.
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

    check(add(2, 3) == 5, "add 2 and 3", failures);
    check(add(-4, 4) == 0, "add -4 and 4", failures);
    check(add(0, 0) == 0, "add 0 and 0", failures);

    // This expectation is wrong on purpose. 2 + 3 is 5, not 6, so the check fails.
    check(add(2, 3) == 6, "add 2 and 3 expects 6", failures);

    std::cout << "Failures: " << failures << "\n";

    // Try: change the expectation in the last check from 6 to 5. Predict the failure count before you press Run.
    return 0;
}
