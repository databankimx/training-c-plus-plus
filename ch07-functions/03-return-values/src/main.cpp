#include <iostream>

// The return type comes before the name. This function gives back an int.
int addFive(int x) {
    return 5 + x;
}

// Overloading: two functions can share a name, as long as their parameters differ.
int add(int x, int y) {
    return x + y;
}

double add(double x, double y) {
    return x + y;
}

int main() {
    int res = addFive(3);
    std::cout << res << "\n";

    res = add(3, 5);
    std::cout << res << "\n";

    int whole = add(8, 5);
    std::cout << "Int: " << whole << "\n";

    double decimal = add(4.3, 6.26);
    std::cout << "Double: " << decimal << "\n";

    // Try: call add(8, 5.0) and predict which overload is chosen, or whether the call is accepted at all.
    return 0;
}
