#include <iostream>

int main() {
    int numbers[3] = {10, 20, 30};
    int* first = numbers;   // the array's name is the address of its first element

    std::cout << *first << "\n";
    std::cout << first[1] << "\n";
    std::cout << *(first + 2) << "\n";

    // Try: set first = &numbers[2], then print *first. Predict the output before you press Run.
    return 0;
}
