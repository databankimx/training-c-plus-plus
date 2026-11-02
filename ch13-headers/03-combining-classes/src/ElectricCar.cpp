#include "ElectricCar.h"

// The colon passes the arguments to the base class's constructor, before this body runs.
ElectricCar::ElectricCar(std::string makeName, std::string modelName, int yearMade, int charge)
    : Car(makeName, modelName, yearMade) {
    if (charge > 0) {
        battery.recharge(charge);
    }
}

void ElectricCar::charge(int amount) {
    battery.recharge(amount);
}

void ElectricCar::showCharge() const {
    battery.displayCharge();
}

void ElectricCar::display() const {
    Car::display();
    battery.displayCharge();
}
