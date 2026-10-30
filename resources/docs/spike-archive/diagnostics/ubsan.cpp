// Diagnostics test 2: does -fsanitize=undefined catch signed integer overflow at run time?
// Signed overflow is undefined behavior in C++, and UBSan reports it instead of silently wrapping.
// Expected output: a line containing "runtime error" and "signed integer overflow".

#include <climits>
#include <iostream>

int main() {
    // volatile stops the compiler from working out the overflow at compile time.
    volatile int big = INT_MAX;
    int result = big + 1;
    std::cout << "result: " << result << "\n";
    return 0;
}
