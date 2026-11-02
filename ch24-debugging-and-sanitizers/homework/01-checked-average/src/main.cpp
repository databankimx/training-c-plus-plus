#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>

// Returns the average of the values. The caller must not pass an empty list, which has no average.
double average(const std::vector<int>& values) {
    assert(!values.empty());
    long long total = 0;
    for (int value : values) {
        total += value;
    }
    return static_cast<double>(total) / static_cast<double>(values.size());
}

int main() {
    std::vector<int> values = {2, 4, 6, 8};
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average: " << average(values) << "\n";
    return 0;
}
