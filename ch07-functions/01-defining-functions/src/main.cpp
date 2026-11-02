#include <iostream>

// A declaration tells the compiler that the function exists, so main can call it before its definition appears.
void greet();

int main() {
    std::cout << "Before the calls\n";
    greet();
    greet();
    std::cout << "After the calls\n";
    return 0;
}

void greet() {
    std::cout << "I just got executed!\n";
}

// Try: move the definition of greet above main, and remove the declaration. Does the program still build?
