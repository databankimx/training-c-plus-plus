#ifndef ELECTRICCAR_H
#define ELECTRICCAR_H

#include "Battery.h"
#include "Car.h"

#include <string>

// An ElectricCar is a Car, so it inherits from Car. It also has a Battery, so it holds one as a member.
class ElectricCar : public Car {
public:
    ElectricCar(std::string makeName, std::string modelName, int yearMade, int charge = 0);
    void charge(int amount = 0);
    void showCharge() const;
    void display() const;

private:
    Battery battery;
};

#endif
