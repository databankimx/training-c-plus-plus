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

// Builds every whole number from 0 to n exactly once, in an order that looks random. The seed is fixed, so the
// order is the same on every run.
std::vector<int> makeData(int n) {
    std::vector<int> values;
    for (int v = 0; v <= n; v++) {
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

// Looks for target from the start, one value at a time. Returns its index, or -1 if it isn't there.
// The comparisons parameter counts every value that was checked.
int linearSearch(const std::vector<int>& values, int target, long long& comparisons) {
    for (std::size_t i = 0; i < values.size(); i++) {
        comparisons++;
        if (values[i] == target) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// Describes a search result for people: the index when the value was found, or NOT FOUND for -1.
std::string describe(int index) {
    if (index == -1) {
        return "NOT FOUND";
    }
    return "index " + std::to_string(index);
}

// Writes trace.js, which the visualizer page loads. It holds one frame for each comparison.
void writeTrace(const std::vector<int>& values, int target, const std::string& path) {
    std::ofstream out(path);
    out << "window.trace = {\n";
    out << "  \"title\": \"Linear search\",\n";
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

    bool first = true;
    bool found = false;
    for (std::size_t i = 0; i < values.size() && !found; i++) {
        if (!first) {
            out << ",\n";
        }
        first = false;
        out << "    {\"array\": " << array << ", \"compare\": [" << i << "], ";
        if (values[i] == target) {
            found = true;
            out << "\"found\": " << i << ", \"message\": \"Found " << target << " at index " << i << " after "
                << (i + 1) << " comparisons.\"}";
        } else {
            out << "\"message\": \"Index " << i << " holds " << values[i] << ", which is not " << target << ".\"}";
        }
    }
    if (!found) {
        if (!first) {
            out << ",\n";
        }
        out << "    {\"array\": " << array << ", \"compare\": [], \"message\": \"Checked all " << values.size()
            << " values. " << target << " is not here.\"}";
    }
    out << "\n  ]\n};\n";
}

int main() {
    // A short list for the visualizer. The values are in no particular order, and the position of each is known.
    std::vector<int> small = {4, 7, 10, 0, 2, 8, 9, 3, 5, 6, 1, 11};
    long long comparisons = 0;
    int index = linearSearch(small, 3, comparisons);
    std::cout << "Data: " << small.size() << " values\n";
    std::cout << "Searching for 3: " << describe(index) << " after " << comparisons << " comparisons\n";
    writeTrace(small, 3, "trace.js");

    // A long list, shuffled, with every whole number from 0 to 1,000. It is counted, not drawn.
    std::vector<int> large = makeData(1000);
    std::cout << "Searching " << withCommas(static_cast<long long>(large.size())) << " values\n";

    // First a valid value, one that is in the list: 737. Where it sits depends on the shuffle, so nothing about the
    // list's order is assumed.
    int wanted = 737;
    comparisons = 0;
    index = linearSearch(large, wanted, comparisons);
    std::cout << "  for 737: " << describe(index) << " after " << withCommas(comparisons) << " comparisons\n";

    // Then an invalid value: 5,000 is outside the range the list covers, so it can't be there.
    comparisons = 0;
    index = linearSearch(large, 5000, comparisons);
    std::cout << "  for 5,000: " << describe(index) << " after " << withCommas(comparisons) << " comparisons\n";

    // Try: search the small list for 12. Predict what the program prints, and how many comparisons it makes.
    return 0;
}
