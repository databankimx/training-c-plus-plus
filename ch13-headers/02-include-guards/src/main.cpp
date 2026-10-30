#include "Battery.h"
#include "Battery.h"  // a second include of the same header, which the guard makes harmless

int main() {
    Battery battery(50);

    battery.recharge(20);
    battery.displayCharge();

    battery.recharge();
    battery.displayCharge();

    battery.recharge(100);
    battery.displayCharge();

    // Try: remove the #ifndef, #define, and #endif lines from Battery.h. Predict the error, then restore them.
    return 0;
}
