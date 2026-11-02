#include <iostream>

// Checks an age. When the age is too low, it throws the age itself, which stops the function at once.
void checkAccess(int age) {
    if (age < 18) {
        throw age;
    }
    std::cout << "Access granted - you are old enough.\n";
}

int main() {
    try {
        checkAccess(25);
        checkAccess(15);
        std::cout << "This line never runs.\n";
    } catch (int myNum) {
        std::cout << "Access denied - you must be at least 18 years old.\n";
        std::cout << "Age is: " << myNum << "\n";
    }

    // Try: change 15 to 30. Predict whether the catch block runs, and which lines print.
    return 0;
}
