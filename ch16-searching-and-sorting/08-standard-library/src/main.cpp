#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

// Formats a non-negative number with a comma between each group of three digits, such as 1,000,000.
std::string withCommas(long long value) {
    std::string digits = std::to_string(value);
    std::string result;
    int length = static_cast<int>(digits.size());
    for (int i = 0; i < length; i++) {
        if (i > 0 && (length - i) % 3 == 0) {
            result += ',';
        }
        result += digits[static_cast<std::size_t>(i)];
    }
    return result;
}

// Builds every whole number from -n to n exactly once, in an order that looks random. The seed is fixed, so the
// order is the same on every run.
std::vector<int> makeSortData(int n) {
    std::vector<int> values;
    for (int v = -n; v <= n; v++) {
        values.push_back(v);
    }
    unsigned long long state = 12345;
    for (std::size_t i = values.size() - 1; i > 0; i--) {
        state = (state * 1103515245ULL + 12345ULL) % 2147483648ULL;
        std::size_t j = static_cast<std::size_t>(state % (i + 1));
        int temp = values[i];
        values[i] = values[j];
        values[j] = temp;
    }
    return values;
}

int main() {
    // The 20-value list from the sorting steps, sorted by the library. The library sort is not counted, since
    // its steps are inside the standard library.
    std::vector<int> small = {14, 3, 19, 7, 1, 12, 20, 5, 16, 9, 2, 17, 6, 11, 18, 4, 13, 8, 15, 10};
    std::sort(small.begin(), small.end());

    std::cout << "Short list: " << small.size() << " values\n";
    std::cout << "Sorted:";
    for (int value : small) {
        std::cout << " " << value;
    }
    std::cout << "\n";

    // Searching a sorted range. binary_search answers yes or no. lower_bound returns the position of the first value
    // that is not smaller than the target; when the value is present, that's its index.
    bool present = std::binary_search(small.begin(), small.end(), 12);
    auto position = std::lower_bound(small.begin(), small.end(), 12);
    std::cout << "Search for 12: " << (present ? "present" : "absent") << " at index "
              << static_cast<long long>(position - small.begin()) << "\n";

    // The timing list: every whole number from -1,000 to 1,000, in a shuffled order. It is sorted and checked,
    // not drawn.
    std::vector<int> timing = makeSortData(1000);
    std::sort(timing.begin(), timing.end());

    std::cout << "\nTiming list: " << withCommas(static_cast<long long>(timing.size()))
              << " values, from -1,000 to 1,000\n";
    std::cout << "First three after sorting: " << timing[0] << " " << timing[1] << " " << timing[2] << "\n";
    std::cout << "Last three after sorting: " << timing[timing.size() - 3] << " " << timing[timing.size() - 2] << " "
              << timing[timing.size() - 1] << "\n";
    std::cout << "Sorted correctly: " << (std::is_sorted(timing.begin(), timing.end()) ? "yes" : "no") << "\n";

    bool found = std::binary_search(timing.begin(), timing.end(), 737);
    bool missing = std::binary_search(timing.begin(), timing.end(), 5000);
    std::cout << "Search for 737: " << (found ? "present" : "absent") << "\n";
    std::cout << "Search for 5,000: " << (missing ? "present" : "absent") << "\n";

    // Try: search the sorted short list for 1 with lower_bound. Predict the index before you press Run.
    return 0;
}
