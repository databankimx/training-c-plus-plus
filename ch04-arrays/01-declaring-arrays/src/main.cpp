#include <iostream>
#include <string>

int main() {
    std::string cars[4] = {"Volvo", "BMW", "Ford", "Mazda"};
    int nums[3] = {10, 20, 30};

    std::cout << cars[0] << "\n";
    std::cout << nums[2] << "\n";

    cars[0] = "Opel";
    nums[2] += 5;

    std::cout << cars[0] << "\n";
    std::cout << nums[2] << "\n";

    // Try: set int index = 4, then print cars[index]. Predict what happens before you press Run.
    return 0;
}
