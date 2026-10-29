#include <iostream>
#include <string>

int main() {
    std::string first = "Hello";
    std::string second = "C++";
    std::string greeting = first + ", " + second + "!";
    std::cout << greeting << "\n";

    std::cout << "Length: " << greeting.size() << "\n";
    std::cout << "First letter: " << greeting[0] << "\n";

    greeting += " Welcome.";
    std::cout << greeting << "\n";

    std::cout << "Tab:\tBackslash:\\ Quote:\"\n";

    // Try: change greeting[0] to greeting[4]. What letter do you expect now?
    return 0;
}
