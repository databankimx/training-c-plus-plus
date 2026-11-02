#include <iostream>

// The function receives only the location of the array's first element, not its size, so the size is passed in separately.
void printNumbers(int numbers[], int count) {
    for (int i = 0; i < count; i++) {
        std::cout << numbers[i] << "\n";
    }
}

int main() {
    int myNumbers[5] = {10, 20, 30, 40, 50};
    printNumbers(myNumbers, 5);

    std::cout << "First three:\n";
    printNumbers(myNumbers, 3);

    // Try: inside printNumbers, add numbers[0] = 99; before the loop. Predict whether main's array changes.
    return 0;
}
