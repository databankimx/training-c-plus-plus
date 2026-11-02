#include <iostream>
#include <vector>

// Counts the values that are at least low and at most high. Both ends of the range are included.
int countInRange(const std::vector<int>& values, int low, int high) {
    int count = 0;
    for (int value : values) {
        if (value >= low && value <= high) {
            count++;
        }
    }
    return count;
}

int main() {
    std::vector<int> values = {1, 2, 3, 4, 5};
    std::cout << "Count between 2 and 4: " << countInRange(values, 2, 4) << "\n";
    std::cout << "Count between 1 and 5: " << countInRange(values, 1, 5) << "\n";
    return 0;
}
