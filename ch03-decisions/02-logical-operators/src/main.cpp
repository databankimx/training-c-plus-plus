#include <iostream>

int main() {
    bool x = true;
    bool y = false;

    std::cout << std::boolalpha;
    std::cout << "x = " << x << ", y = " << y << "\n";
    std::cout << "x && y: " << (x && y) << "\n";
    std::cout << "x || y: " << (x || y) << "\n";
    std::cout << "!x: " << !x << "\n";
    std::cout << "!y: " << !y << "\n";

    bool p = true;
    bool q = false;

    bool myXor = (p || q) && !(p && q); // example explaining the logic
    std::cout << "(p || q) && !(p && q): " << myXor << "\n";

    myXor = p != q; // simple example with less obvious logic
    std::cout << "p != q: " << myXor << "\n";

    std::cout << "(true || false) && false: " << ((true || false) && false) << "\n";

    int age = 25;
    bool has_ticket = false;
    std::cout << "Adult and has ticket: " << (age >= 18 && has_ticket) << "\n";
    std::cout << "Adult or has ticket: " << (age >= 18 || has_ticket) << "\n";

    // The right-hand side of && and || is only checked when the left-hand side doesn't decide the answer.
    int count = 0;
    bool ok = (count != 0) && (10 / count > 1);
    std::cout << "Short-circuit result: " << ok << "\n";

    // Try: change count to 2. Predict the result before you press Run.
    return 0;
}
