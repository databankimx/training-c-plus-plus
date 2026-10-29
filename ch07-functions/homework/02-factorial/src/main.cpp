#include <iostream>

int factorialRecursive(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorialRecursive(n - 1);
}

int factorialLoop(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    for (int n = 0; n <= 10; n++) {
        int recursive = factorialRecursive(n);
        int loop = factorialLoop(n);
        std::cout << n << "! = " << recursive << (recursive == loop ? " (agree)" : " (disagree)") << "\n";
    }

    return 0;
}
