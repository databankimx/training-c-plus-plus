#include "Car.h"
#include "ElectricCar.h"

int main() {
    Car car("Ford", "Escort", 1986);
    car.display();

    ElectricCar eCar("Nissan", "Leaf", 2015, 25);
    eCar.display();

    eCar.charge(25);
    eCar.showCharge();

    eCar.charge();
    eCar.showCharge();

    // Try: call eCar.charge(200) and predict the charge shown. Then predict what happens to the charge if you call it with -5.
    return 0;
}
