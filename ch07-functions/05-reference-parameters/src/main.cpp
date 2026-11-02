#include <iostream>

// The & after int makes x and y references to the caller's variables, so the swap reaches them.
void swapNums(int& x, int& y) {
    int z = x;
    x = y;
    y = z;
}

int main() {
    int firstNum = 10;
    int secondNum = 20;
    std::cout << firstNum << " " << secondNum << "\n";

    swapNums(firstNum, secondNum);
    std::cout << firstNum << " " << secondNum << "\n";

    // Try: remove the & from both parameters. Predict the second line of output before you press Run.
    return 0;
}
