#include "Car.h"

#include <iostream>

// The constructor's body copies its arguments into the members, as in the constructors chapter.
Car::Car(std::string makeName, std::string modelName, int yearMade) {
    make = makeName;
    model = modelName;
    year = yearMade;
}

void Car::display() const {
    std::cout << "Make: " << make << "\n";
    std::cout << "Model: " << model << "\n";
    std::cout << "Year: " << year << "\n\n";
}
