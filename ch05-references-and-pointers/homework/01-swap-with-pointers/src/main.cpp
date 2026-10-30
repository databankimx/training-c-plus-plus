#include <iostream>

void swapValues(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main() {
    std::cout << "Enter a: " << std::flush;
    int a = 0;
    std::cin >> a;

    std::cout << "Enter b: " << std::flush;
    int b = 0;
    std::cin >> b;

    swapValues(&a, &b);
    std::cout << "a = " << a << ", b = " << b << "\n";

    return 0;
}
