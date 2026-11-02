#include "Battery.h"

#include <iostream>

Battery::Battery(int cap) {
    capacity = cap;
}

// An amount of 0 means a full recharge. Any other amount adds to the charge, up to the capacity.
void Battery::recharge(int amount) {
    if (amount == 0) {
        charge = capacity;
    } else {
        charge += amount;
    }

    if (charge > capacity) {
        charge = capacity;
    }
}

void Battery::displayCharge() const {
    std::cout << "Charge: " << charge << "\n";
    std::cout << "Capacity: " << capacity << "\n\n";
}
