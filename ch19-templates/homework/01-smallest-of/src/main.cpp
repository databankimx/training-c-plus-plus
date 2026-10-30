#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

// Returns the smallest value in the vector. The vector must hold at least one value.
template <typename T>
T smallestOf(const std::vector<T>& values) {
    T smallest = values[0];
    for (std::size_t i = 1; i < values.size(); i++) {
        if (values[i] < smallest) {
            smallest = values[i];
        }
    }
    return smallest;
}

int main() {
    std::vector<int> numbers = {5, 2, 9};
    std::vector<std::string> words = {"pear", "apple", "fig"};

    std::cout << "Smallest number: " << smallestOf(numbers) << "\n";
    std::cout << "Smallest word: " << smallestOf(words) << "\n";
    return 0;
}
