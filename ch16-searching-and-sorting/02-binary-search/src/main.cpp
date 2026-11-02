#include <cstddef>
#include <fstream>
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

// Describes a search result for people: the index when the value was found, or NOT FOUND for -1.
std::string describe(int index) {
    if (index == -1) {
        return "NOT FOUND";
    }
    return "index " + std::to_string(index);
}

// Looks for target from the start, one value at a time. Used here for comparison with binary search.
int linearSearch(const std::vector<int>& values, int target, long long& comparisons) {
    for (std::size_t i = 0; i < values.size(); i++) {
        comparisons++;
        if (values[i] == target) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// Looks for target in a sorted list. It checks the middle, then throws away the half that can't hold the target.
// The low and high indexes mark the part of the list still being searched.
int binarySearch(const std::vector<int>& values, int target, long long& comparisons) {
    int low = 0;
    int high = static_cast<int>(values.size()) - 1;
    while (low <= high) {
        int middle = (low + high) / 2;
        comparisons++;
        if (values[static_cast<std::size_t>(middle)] == target) {
            return middle;
        }
        if (values[static_cast<std::size_t>(middle)] < target) {
            low = middle + 1;
        } else {
            high = middle - 1;
        }
    }
    return -1;
}

// Writes trace.js, which the visualizer page loads. Each frame shows the range still being searched.
void writeTrace(const std::vector<int>& values, int target, const std::string& path) {
    std::ofstream out(path);
    out << "window.trace = {\n";
    out << "  \"title\": \"Binary search\",\n";
    out << "  \"target\": " << target << ",\n";
    out << "  \"frames\": [\n";

    std::string array = "[";
    for (std::size_t i = 0; i < values.size(); i++) {
        if (i > 0) {
            array += ", ";
        }
        array += std::to_string(values[i]);
    }
    array += "]";

    int low = 0;
    int high = static_cast<int>(values.size()) - 1;
    int count = 0;
    bool first = true;
    bool found = false;
    while (low <= high && !found) {
        int middle = (low + high) / 2;
        std::size_t m = static_cast<std::size_t>(middle);
        count++;
        if (!first) {
            out << ",\n";
        }
        first = false;
        out << "    {\"array\": " << array << ", \"range\": [" << low << ", " << high << "], \"compare\": [" << middle
            << "], ";
        if (values[m] == target) {
            found = true;
            out << "\"found\": " << middle << ", \"message\": \"Found " << target << " at index " << middle << " after "
                << count << " comparisons.\"}";
        } else if (values[m] < target) {
            out << "\"message\": \"Index " << middle << " holds " << values[m] << ", which is less than " << target
                << ", so the lower half is thrown away.\"}";
            low = middle + 1;
        } else {
            out << "\"message\": \"Index " << middle << " holds " << values[m] << ", which is more than " << target
                << ", so the upper half is thrown away.\"}";
            high = middle - 1;
        }
    }
    if (!found) {
        if (!first) {
            out << ",\n";
        }
        out << "    {\"array\": " << array << ", \"compare\": [], \"message\": \"The range is empty. " << target
            << " is not here.\"}";
    }
    out << "\n  ]\n};\n";
}

int main() {
    // A short sorted list for the visualizer. Each value's position is easy to read off.
    std::vector<int> small = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    long long comparisons = 0;
    int index = binarySearch(small, 7, comparisons);
    std::cout << "Sorted list: " << small.size() << " values\n";
    std::cout << "Searching for 7: " << describe(index) << " after " << comparisons << " comparisons\n";
    writeTrace(small, 7, "trace.js");

    // A long sorted list, 0 to 1,000, with each value sitting at the index that matches it.
    std::vector<int> large;
    for (int v = 0; v <= 1000; v++) {
        large.push_back(v);
    }
    std::cout << "Sorted list: " << withCommas(static_cast<long long>(large.size())) << " values\n";

    comparisons = 0;
    index = binarySearch(large, 737, comparisons);
    long long linearComparisons = 0;
    linearSearch(large, 737, linearComparisons);
    std::cout << "  for 737: " << describe(index) << " after " << comparisons << " comparisons (linear search: "
              << withCommas(linearComparisons) << ")\n";

    comparisons = 0;
    index = binarySearch(large, 5000, comparisons);
    std::cout << "  for 5,000: " << describe(index) << " after " << comparisons << " comparisons\n";

    // Try: search the sorted list for 12. Predict the index, and the comparison count, before you press Run.
    return 0;
}
