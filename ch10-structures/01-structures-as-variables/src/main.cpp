#include <iostream>
#include <string>

// A structure groups related values under one name. Each value is a member.
struct Car {
    std::string brand;
    std::string model;
    int year;
};

int main() {
    Car myCar1;
    myCar1.brand = "BMW";
    myCar1.model = "X5";
    myCar1.year = 1999;

    Car myCar2;
    myCar2.brand = "Ford";
    myCar2.model = "Mustang";
    myCar2.year = 1969;

    std::cout << myCar1.brand << " " << myCar1.model << " " << myCar1.year << "\n";
    std::cout << myCar2.brand << " " << myCar2.model << " " << myCar2.year << "\n";

    // Try: add a member called color, of type std::string, and print it for myCar1 without setting it. What does it print?
    return 0;
}
