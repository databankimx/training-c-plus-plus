#include "Car.h"

int main() {
    Car car("Ford", "Escort", 1986);
    car.display();

    Car second("Nissan", "Leaf", 2015);
    second.display();

    // Try: remove the #include "Car.h" line. Predict the error, then restore it.
    return 0;
}
