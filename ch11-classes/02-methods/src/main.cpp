#include <iostream>
#include <string>

class Car {
public:
    std::string brand;
    std::string model;
    int year;

    // A method defined inside the class. It can use the object's own members.
    std::string name() const {
        return brand + " " + model;
    }

    // A method declared here and defined below the class.
    std::string fullName() const;
};

std::string Car::fullName() const {
    return std::to_string(year) + " " + brand + " " + model;
}

int main() {
    Car myCar;
    myCar.brand = "Ford";
    myCar.model = "Mustang";
    myCar.year = 1969;

    std::cout << myCar.name() << "\n";
    std::cout << myCar.fullName() << "\n";

    // Try: remove const from name() and fullName(). Does the program still build?
    return 0;
}
