#include <iostream>
#include <string>

struct Car {
    std::string brand;
    std::string model;
    int year;
};

// Builds a car and returns it. The caller receives the whole structure.
Car makeCar(std::string brand, std::string model, int year) {
    Car car;
    car.brand = brand;
    car.model = model;
    car.year = year;
    return car;
}

// Receives a copy of the car. Changing the copy here leaves the caller's car alone.
void describe(Car car) {
    std::cout << car.brand << " " << car.model << " " << car.year << "\n";
}

// Receives a reference, so changing the year here changes the caller's car.
void makeOlder(Car& car) {
    car.year -= 10;
}

int main() {
    Car mine = makeCar("BMW", "X5", 1999);
    describe(mine);

    makeOlder(mine);
    describe(mine);

    Car cars[2] = {makeCar("Ford", "Mustang", 1969), makeCar("Fiat", "500", 2010)};
    for (Car car : cars) {
        describe(car);
    }

    // Try: change describe so its parameter is Car& car. Predict whether makeOlder still works, and whether describe changes.
    return 0;
}
