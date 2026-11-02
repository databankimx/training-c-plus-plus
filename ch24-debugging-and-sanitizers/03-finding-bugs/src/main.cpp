#include <iostream>

// Adds the whole numbers from 1 up to n. The program is meant to include n itself.
int sumTo(int n) {
    int total = 0;
    for (int i = 1; i < n; i++) {
        total += i;
    }
    return total;
}

int main() {
    // The sum of 1 through 10 is 55, but this program prints 45. Find the fault with the debugger.
    std::cout << "Sum of 1 to 10: " << sumTo(10) << "\n";

    // Try: set a breakpoint on the total += i line, and step through the loop. Watch total and i, and note the
    // last value of i that the loop uses.
    return 0;
}
