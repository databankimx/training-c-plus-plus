#include <iostream>
#include <iterator>
#include <string>

int main() {
    int partial[5] = {7, 8};
    std::cout << partial[0] << " " << partial[1] << " " << partial[2] << " " << partial[4] << "\n";

    std::string cars[] = {"Volvo", "BMW", "Ford", "Mazda", "Tesla"};
    std::cout << "Cars: " << std::size(cars) << "\n";
    std::cout << "Last: " << cars[std::size(cars) - 1] << "\n";

    int squares[3];
    squares[0] = 1;
    squares[1] = 4;
    squares[2] = 9;
    std::cout << squares[2] << "\n";

    // Try: change partial to int partial[5] = {7, 8, 9, 10, 11}. Predict the first line of output.
    return 0;
}
