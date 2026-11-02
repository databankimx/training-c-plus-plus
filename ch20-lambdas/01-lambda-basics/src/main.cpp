#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    // A lambda is a function written where it's used. This one squares its argument.
    auto square = [](int x) { return x * x; };
    std::cout << "Square of 4: " << square(4) << "\n";

    // The third argument to std::sort is a comparison. This lambda answers "should a come before b?" with a > b,
    // which sorts the values from largest to smallest.
    std::vector<int> values = {3, 1, 4, 1, 5, 9, 2, 6};
    std::sort(values.begin(), values.end(), [](int a, int b) { return a > b; });

    std::cout << "Descending:";
    for (int value : values) {
        std::cout << " " << value;
    }
    std::cout << "\n";

    // Try: change the comparison to a < b, and predict the order before you press Run.
    return 0;
}
