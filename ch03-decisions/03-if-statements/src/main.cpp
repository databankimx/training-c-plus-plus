#include <iostream>
#include <string>

int main() {
    int x = 20;
    int y = 10;

    if (x == y) {
        std::cout << "x equals y\n";
    }
    if (x > y) {
        std::cout << "x is greater than y\n";
    }
    if (x < y) {
        std::cout << "x is less than y\n";
    }

    int age = 16;
    int voting_age = 18;
    if (age >= voting_age) {
        std::cout << "You can vote!\n";
    } else {
        int wait = voting_age - age;
        std::cout << "You will be able to vote in " << wait << " years.\n";
    }

    int driver_age = 20;
    if (driver_age >= 21) {
        std::cout << "You drive, vote, and rent a car.\n";
    } else if (driver_age >= 18) {
        std::cout << "You can drive and vote, but you can't rent a car.\n";
    } else if (driver_age >= 16) {
        std::cout << "You can drive, but you can't vote or rent a car.\n";
    } else {
        std::cout << "You can't drive, vote, or rent a car.\n";
    }

    std::string size = (x > y) ? "large" : "small";
    std::cout << "x is " << size << "\n";

    int score = 75;
    if (score >= 90) {
        std::cout << "Excellent\n";
    } else if (score >= 70) {
        std::cout << "Good\n";
    }
    // No final else: a score below 70 prints nothing, and that's the intended result.

    int items = 12;
    if (items > 10) {
        std::cout << "Chained: bulk discount\n";
    } else if (items > 5) {
        std::cout << "Chained: free shipping\n";
    }

    if (items > 10) {
        std::cout << "Independent: bulk discount\n";
    }
    if (items > 5) {
        std::cout << "Independent: free shipping\n";
    }

    // Try: change driver_age to 17. Predict which message prints before you press Run.
    return 0;
}
