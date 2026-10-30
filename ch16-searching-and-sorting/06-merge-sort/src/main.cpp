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

// The values as text, such as [5, 2, 8].
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

// Two indexes as text, such as [2, 7].
std::string indexPair(std::size_t a, std::size_t b) {
    return "[" + std::to_string(a) + ", " + std::to_string(b) + "]";
}

// Writes one frame of trace.js. A comma goes before every frame except the first. The range is the part of the
// list being worked on; the visualizer fades everything outside it.
void writeFrame(std::ofstream& out, bool& first, const std::string& array, const std::string& compare,
                const std::string& swap, const std::string& sorted, const std::string& range,
                const std::string& message) {
    if (!first) {
        out << ",\n";
    }
    first = false;
    out << "    {\"array\": " << array << ", \"compare\": " << compare << ", \"swap\": " << swap
        << ", \"sorted\": " << sorted << ", \"range\": " << range << ", \"message\": \"" << message << "\"}";
}

// Merges the two sorted runs values[lo..mid-1] and values[mid..hi-1] into one sorted run. Each comparison takes the
// smaller of the two front values, and stops when one run is used up. The rest of the other run is then copied across.
void merge(std::vector<int>& values, std::size_t lo, std::size_t mid, std::size_t hi, long long& comparisons,
           std::ofstream* trace, bool& first) {
    std::vector<int> merged;
    merged.reserve(hi - lo);
    std::size_t left = lo;
    std::size_t right = mid;
    std::string range = indexRange(lo, hi - 1);
    while (left < mid && right < hi) {
        comparisons++;
        if (trace != nullptr) {
            std::string message = "Compare " + std::to_string(values[left]) + " from the left run with " +
                                  std::to_string(values[right]) + " from the right run. Keep the smaller.";
            writeFrame(*trace, first, arrayText(values), indexPair(left, right), "[]", "[]", range, message);
        }
        if (values[left] <= values[right]) {
            merged.push_back(values[left]);
            left++;
        } else {
            merged.push_back(values[right]);
            right++;
        }
    }
    while (left < mid) {
        merged.push_back(values[left]);
        left++;
    }
    while (right < hi) {
        merged.push_back(values[right]);
        right++;
    }
    for (std::size_t k = 0; k < merged.size(); k++) {
        values[lo + k] = merged[k];
    }
    if (trace != nullptr) {
        writeFrame(*trace, first, arrayText(values), "[]", indexRange(lo, hi - 1), "[]", range,
                   "These values are now merged into order.");
    }
}

// Merge sort. A run of one value is already sorted. Otherwise the run is split into two halves, each half is sorted
// by the same method, and the two sorted halves are merged. Every level of splitting halves the work.
void mergeSort(std::vector<int>& values, std::size_t lo, std::size_t hi, long long& comparisons,
               std::ofstream* trace, bool& first) {
    if (hi - lo <= 1) {
        return;
    }
    std::size_t mid = lo + (hi - lo) / 2;
    if (trace != nullptr) {
        writeFrame(*trace, first, arrayText(values), "[]", "[]", "[]", indexRange(lo, hi - 1),
                   "Split these " + std::to_string(hi - lo) + " values into two halves.");
    }
    mergeSort(values, lo, mid, comparisons, trace, first);
    mergeSort(values, mid, hi, comparisons, trace, first);
    merge(values, lo, mid, hi, comparisons, trace, first);
}

int main() {
    // A short list for the visualizer. It holds the values 1 through 20, each once, in a scrambled order. It is
    // non-negative, so each bar's height matches its value.
    std::vector<int> small = {14, 3, 19, 7, 1, 12, 20, 5, 16, 9, 2, 17, 6, 11, 18, 4, 13, 8, 15, 10};
    long long comparisons = 0;
    bool first = true;
    std::ofstream trace("trace.js");
    trace << "window.trace = {\n";
    trace << "  \"title\": \"Merge sort\",\n";
    trace << "  \"frames\": [\n";
    mergeSort(small, 0, small.size(), comparisons, &trace, first);
    writeFrame(trace, first, arrayText(small), "[]", "[]", indexRange(0, small.size() - 1), "[]",
               "Sorted. " + std::to_string(comparisons) + " comparisons.");
    trace << "\n  ]\n};\n";
    trace.close();

    std::cout << "Visualized list: " << small.size() << " values\n";
    std::cout << "Sorted:";
    for (int value : small) {
        std::cout << " " << value;
    }
    std::cout << "\nComparisons: " << comparisons << "\n";

    // A long list of every whole number from -1,000 to 1,000, in a shuffled order. It is counted, not drawn.
    std::vector<int> timing = makeSortData(1000);
    comparisons = 0;
    bool unused = true;
    mergeSort(timing, 0, timing.size(), comparisons, nullptr, unused);

    bool sorted = true;
    for (std::size_t i = 1; i < timing.size(); i++) {
        if (timing[i - 1] > timing[i]) {
            sorted = false;
        }
    }
    std::cout << "\nTiming list: " << withCommas(static_cast<long long>(timing.size()))
              << " values, from -1,000 to 1,000\n";
    std::cout << "First three after sorting: " << timing[0] << " " << timing[1] << " " << timing[2] << "\n";
    std::cout << "Last three after sorting: " << timing[timing.size() - 3] << " " << timing[timing.size() - 2] << " "
              << timing[timing.size() - 1] << "\n";
    std::cout << "Comparisons: " << withCommas(comparisons) << "\n";
    std::cout << "Sorted correctly: " << (sorted ? "yes" : "no") << "\n";

    // Try: sort the values 1 through 20 in order, and predict the comparison count before you press Run.
    return 0;
}
