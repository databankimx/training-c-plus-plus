#include <iostream>
#include <string>

// The base class. Everything in it is inherited by the classes derived from it.
class Vehicle {
public:
    std::string brand = "Ford";

    void honk() const {
        std::cout << "Toot, toot!\n";
    }
};

// Car inherits from Vehicle, so a Car has brand and honk() as well as its own model.
class Car : public Vehicle {
public:
    std::string model = "Mustang";
};

// SportsCar inherits from Car, which inherits from Vehicle. Inheritance can continue down a chain.
class SportsCar : public Car {
public:
    int topSpeed = 180;
};

int main() {
    Car myCar;
    myCar.honk();
    std::cout << myCar.brand << " " << myCar.model << "\n";

    SportsCar fast;
    fast.honk();
    std::cout << fast.brand << " " << fast.model << " " << fast.topSpeed << "\n";

    // Try: add a method called describe() to Vehicle, and call it on fast. Predict whether SportsCar can use it.
    return 0;
}
