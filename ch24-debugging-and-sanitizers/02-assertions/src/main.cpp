#include <cassert>
#include <iostream>

// Divides a by b. The caller must never pass zero, so an assertion checks that promise.
int divide(int a, int b) {
    assert(b != 0);
    return a / b;
}

int main() {
    // An assertion states a condition that must be true. In a Debug build, a false one stops the program with a
    // message that names the file, line, and condition.
    assert(divide(10, 2) == 5);
    assert(divide(9, 3) == 3);

    std::cout << "All assertions passed\n";

    // Try: call divide(1, 0) before the message, and predict what the program prints and its exit code.
    return 0;
}
