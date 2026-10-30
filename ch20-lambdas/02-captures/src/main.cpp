#include <iostream>

int main() {
    // [factor] captures a copy of factor when the lambda is created. Changing factor afterward doesn't affect it.
    int factor = 3;
    auto scaleByCopy = [factor](int x) { return x * factor; };
    factor = 10;
    std::cout << "Scaled by copy: " << scaleByCopy(5) << "\n";

    // [&total] captures a reference to total. Each call changes the original variable.
    int total = 0;
    auto addTo = [&total](int x) { total += x; };
    addTo(4);
    addTo(6);
    std::cout << "Total by reference: " << total << "\n";

    // Try: change the capture of scaleByCopy to [&factor]. Predict the value printed for it, before you press Run.
    return 0;
}
