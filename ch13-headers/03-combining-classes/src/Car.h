#ifndef CAR_H
#define CAR_H

#include <string>

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
