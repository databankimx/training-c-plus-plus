#ifndef BATTERY_H
#define BATTERY_H

class Battery {
public:
    Battery(int cap = 100);
    void recharge(int amount = 0);
    void displayCharge() const;

private:
    int charge = 0;
    int capacity = 100;
};

#endif
