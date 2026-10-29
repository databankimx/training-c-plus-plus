#include <iostream>
#include <string>

int main() {
    std::string letters[2][4] = {
        {"A", "B", "C", "D"},
        {"E", "F", "G", "H"}
    };

    std::cout << letters[1][2] << "\n";
    std::cout << letters[0][3] << "\n";

    int grid[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    std::cout << "Center: " << grid[1][1] << "\n";
    std::cout << "Sum of the first row: " << grid[0][0] + grid[0][1] + grid[0][2] << "\n";

    grid[2][0] = 0;
    std::cout << "Bottom-left: " << grid[2][0] << "\n";

    // Try: predict the value of grid[1][2] before you press Run.
    return 0;
}
