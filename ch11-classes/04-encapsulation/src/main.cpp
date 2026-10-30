#include <iostream>
#include <stdexcept>
#include <string>

class Car {
public:
    Car(std::string mk, std::string mod, int yr) {
        brand = mk;
        model = mod;
        setYear(yr);
    }

    // Getters let the outside world read the private members.
    std::string getBrand() const { return brand; }
    int getYear() const { return year; }

    // A setter checks the value before it stores it. A bad year is refused, and the object is left unchanged.
    void setYear(int yr) {
        if (yr < 1886) {
            throw std::invalid_argument("year is before cars existed");
        }
        year = yr;
    }

    std::string name() const {
        return std::to_string(year) + " " + brand + " " + model;
    }

private:
    std::string brand;
    std::string model;
    int year = 0;
};

int main() {
    Car myCar("Ford", "Mustang", 1969);
    std::cout << myCar.name() << "\n";

    myCar.setYear(2014);
    std::cout << myCar.name() << "\n";

    try {
        myCar.setYear(1700);
    } catch (const std::invalid_argument& error) {
        std::cout << error.what() << "\n";
    }
    std::cout << myCar.name() << "\n";

    // Try: add the line myCar.year = 1700; and predict whether it compiles.
    return 0;
}
