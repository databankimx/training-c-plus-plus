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

// Builds every whole number from -n to n exactly once, in an order that looks random. The seed is fixed, so the
// order is the same on every run. Used for the timing list, which is counted and not drawn.
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

// The values as JavaScript-style text, such as [5, 2, 8].
std::string arrayText(const std::vector<int>& values) {
    std::string text = "[";
    for (std::size_t i = 0; i < values.size(); i++) {
        if (i > 0) {
            text += ", ";
        }
        text += std::to_string(values[i]);
    }
    return text + "]";
}

// The indexes from first to last, inclusive, as text such as [3, 4, 5]. Empty when first is past last.
std::string indexRange(std::size_t first, std::size_t last) {
    std::string text = "[";
    bool any = false;
    for (std::size_t i = first; i <= last; i++) {
        if (any) {
            text += ", ";
        }
        text += std::to_string(i);
        any = true;
    }
    return text + "]";
}

// Writes one frame of trace.js. A comma goes before every frame except the first.
void writeFrame(std::ofstream& out, bool& first, const std::string& array, const std::string& compare,
                const std::string& swap, const std::string& sorted, const std::string& message) {
    if (!first) {
        out << ",\n";
    }
    first = false;
    out << "    {\"array\": " << array << ", \"compare\": " << compare << ", \"swap\": " << swap
        << ", \"sorted\": " << sorted << ", \"message\": \"" << message << "\"}";
}

// Bubble sort. Each pass walks along the list, comparing neighbors and swapping them when they're out of order.
// Every pass puts the largest remaining value in its final place at the end. A pass with no swaps means the list
// is sorted, so the sort stops early. When trace is not null, every comparison and swap is written as a frame.
void bubbleSort(std::vector<int>& values, long long& comparisons, long long& swaps, std::ofstream* trace,
                bool& first) {
    std::size_t n = values.size();
    for (std::size_t pass = 0; pass + 1 < n; pass++) {
        bool swapped = false;
        std::size_t placed = n - pass;   // positions placed..n-1 already hold their final values
        for (std::size_t j = 0; j + 1 < n - pass; j++) {
            comparisons++;
            int left = values[j];
            int right = values[j + 1];
            bool out_of_order = left > right;
            if (trace != nullptr) {
                std::string message = "Compare " + std::to_string(left) + " and " + std::to_string(right) + ". " +
                                      (out_of_order ? "They are out of order, so swap them."
                                                    : "They are in order, so leave them.");
                writeFrame(*trace, first, arrayText(values), indexRange(j, j + 1), "[]", indexRange(placed, n - 1),
                           message);
            }
            if (out_of_order) {
                values[j] = right;
                values[j + 1] = left;
                swaps++;
                swapped = true;
                if (trace != nullptr) {
                    writeFrame(*trace, first, arrayText(values), "[]", indexRange(j, j + 1),
                               indexRange(placed, n - 1), "The two values are now in order.");
                }
            }
        }
        if (!swapped) {
            break;
        }
    }
    if (trace != nullptr) {
        writeFrame(*trace, first, arrayText(values), "[]", "[]", indexRange(0, n - 1),
                   "Sorted. " + std::to_string(comparisons) + " comparisons and " + std::to_string(swaps) +
                       " swaps.");
    }
}

int main() {
    // A short list for the visualizer. It holds only non-negative values, each of 1 through 20 once, so each bar's
    // height matches its value.
    std::vector<int> small = {14, 3, 19, 7, 1, 12, 20, 5, 16, 9, 2, 17, 6, 11, 18, 4, 13, 8, 15, 10};
    long long comparisons = 0;
    long long swaps = 0;
    bool first = true;
    std::ofstream trace("trace.js");
    trace << "window.trace = {\n";
    trace << "  \"title\": \"Bubble sort\",\n";
    trace << "  \"frames\": [\n";
    bubbleSort(small, comparisons, swaps, &trace, first);
    trace << "\n  ]\n};\n";
    trace.close();

    std::cout << "Visualized list: " << small.size() << " values\n";
    std::cout << "Sorted:";
    for (int value : small) {
        std::cout << " " << value;
    }
    std::cout << "\nComparisons: " << comparisons << ", swaps: " << swaps << "\n";

    // A long list of every whole number from -1,000 to 1,000, in a shuffled order. It is counted, not drawn.
    std::vector<int> timing = makeSortData(1000);
    comparisons = 0;
    swaps = 0;
    bool unused = true;
    bubbleSort(timing, comparisons, swaps, nullptr, unused);

    bool sorted = true;
    for (std::size_t i = 1; i < timing.size(); i++) {
        if (timing[i - 1] > timing[i]) {
            sorted = false;
        }
    }
    std::cout << "\nTiming list: " << withCommas(static_cast<long long>(timing.size())) << " values, from -1,000 to 1,000\n";
    std::cout << "First three after sorting: " << timing[0] << " " << timing[1] << " " << timing[2] << "\n";
    std::cout << "Last three after sorting: " << timing[timing.size() - 3] << " " << timing[timing.size() - 2] << " "
              << timing[timing.size() - 1] << "\n";
    std::cout << "Comparisons: " << withCommas(comparisons) << ", swaps: " << withCommas(swaps) << "\n";
    std::cout << "Sorted correctly: " << (sorted ? "yes" : "no") << "\n";

    // Try: change the visualized list to 20 down to 1, in reverse order. Predict the comparison count before you press
    // Run. Reversed input is the worst case for bubble sort.
    return 0;
}
