#include <iostream>
#include <string>

// A function template. T is a placeholder for a type, and the compiler writes a version of the function for each
// type it's used with.
template <typename T>
T largerOf(T a, T b) {
    return a > b ? a : b;
}

int main() {
    // The compiler works out T from the arguments: here int, then double.
    std::cout << largerOf(3, 7) << "\n";
    std::cout << largerOf(2.5, 1.5) << "\n";

    // The type can also be written out, which is needed when the arguments don't settle it.
    std::cout << largerOf<std::string>("apple", "banana") << "\n";

    // Try: call largerOf(3, 2.5). Predict whether the compiler accepts it, and why, before you press Run.
    return 0;
}
