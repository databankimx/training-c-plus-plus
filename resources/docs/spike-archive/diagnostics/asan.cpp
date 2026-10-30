// Diagnostics test 3: does -fsanitize=address link and run with MinGW g++, and does it catch a heap overflow?
// Expected output: a report containing "AddressSanitizer" and "heap-buffer-overflow".
// If the program links but prints nothing useful, or fails to link, that's the answer we need.

#include <iostream>

int main() {
    int* data = new int[4]{1, 2, 3, 4};
    std::cout << "reading past the end of the array\n";
    // Index 10 is outside the four elements allocated above.
    std::cout << "value: " << data[10] << "\n";
    delete[] data;
    return 0;
}
