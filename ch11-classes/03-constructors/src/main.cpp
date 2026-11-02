#include <iostream>
#include <string>

class Car {
public:
    // A constructor has the class's name and no return type. It runs when an object is created.
    Car(std::string mk, std::string mod, int yr);

    std::string brand;
    std::string model;
    int year;

    std::string name() const {
        return std::to_string(year) + " " + brand + " " + model;
    }
};

// The constructor's body sets the members from its arguments.
Car::Car(std::string mk, std::string mod, int yr) {
    brand = mk;
    model = mod;
    year = yr;
}

int main() {
    Car myCar1 = Car("Ford", "Mustang", 1969);
    std::cout << myCar1.name() << "\n";

    Car myCar2("Dodge", "Challenger", 2014);
    std::cout << myCar2.name() << "\n";

    // Try: create a third car with Car myCar3{"Fiat", "500", 2010};. Predict whether it compiles, then compare with the structure chapter.
    return 0;
}
