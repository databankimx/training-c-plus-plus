#include <iostream>
#include <string>

// A class groups data and the operations on it. Each variable of the class is an object.
class Car {
public:
    std::string brand;
    std::string model;
    int year;
};

int main() {
    Car carObj1;
    carObj1.brand = "BMW";
    carObj1.model = "X5";
    carObj1.year = 1999;

    Car carObj2;
    carObj2.brand = "Ford";
    carObj2.model = "Mustang";
    carObj2.year = 1969;

    std::cout << carObj1.brand << " " << carObj1.model << " " << carObj1.year << "\n";
    std::cout << carObj2.brand << " " << carObj2.model << " " << carObj2.year << "\n";

    // Try: change public to private, above brand. Predict whether main still compiles.
    return 0;
}
