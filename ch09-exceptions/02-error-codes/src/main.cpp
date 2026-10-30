#include <iostream>

// Returns normally for ages 18 to 64. Throws -1 for an age under 18, and -2 for 65 or over.
void checkAccess(int age) {
    if (age < 18) {
        throw -1;
    }
    if (age >= 65) {
        throw -2;
    }
    std::cout << "Access granted.\n";
}

int main() {
    std::cout << "Enter your age: " << std::flush;
    int age = 0;
    std::cin >> age;

    try {
        checkAccess(age);
    } catch (int err) {
        switch (err) {
            case -1:
                std::cout << "Access denied! Underage!\n";
                break;
            case -2:
                std::cout << "Access denied! Too old!\n";
                break;
            default:
                std::cout << "Access denied! (unknown error)\n";
                break;
        }
    }

    // Try: enter 65, then 64. Predict the message for each before you press Run again.
    return 0;
}
