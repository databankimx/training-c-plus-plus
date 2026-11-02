#ifndef CAR_H
#define CAR_H

#include <string>

// The header declares what a Car is and what it can do. The definitions live in Car.cpp.
class Car {
public:
    Car(std::string makeName, std::string modelName, int yearMade);
    void display() const;

private:
    std::string make;
    std::string model;
    int year;
};

#endif
