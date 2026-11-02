#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

// Returns the index of the first value that is not smaller than target, or the size of the list when every value is
// smaller. The range [low, high) is the part still being searched.
std::size_t lowerBound(const std::vector<int>& values, int target) {
    std::size_t low = 0;
    std::size_t high = values.size();
    while (low < high) {
        std::size_t middle = low + (high - low) / 2;
        if (values[middle] < target) {
            low = middle + 1;
        } else {
            high = middle;
        }
    }
    return low;
}

int main() {
    std::vector<int> values = {1, 3, 3, 3, 5, 8};
    int targets[] = {3, 4, 9};

    bool matches = true;
    for (int target : targets) {
        std::size_t mine = lowerBound(values, target);
        std::size_t library = static_cast<std::size_t>(std::lower_bound(values.begin(), values.end(), target) -
                                                       values.begin());
        std::cout << "lowerBound(" << target << "): " << mine << "\n";
        if (mine != library) {
            matches = false;
        }
    }
    std::cout << "Matches std::lower_bound: " << (matches ? "yes" : "no") << "\n";

    // Try: search for 0, which is smaller than every value. Predict the index before you press Run.
    return 0;
}
