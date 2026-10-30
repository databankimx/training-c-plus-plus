#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int evenCount = 0;
    int evenSum = 0;

    // The lambda captures both totals by reference, so changes made inside it are visible after for_each returns.
    std::for_each(numbers.begin(), numbers.end(), [&evenCount, &evenSum](int value) {
        if (value % 2 == 0) {
            evenCount++;
            evenSum += value;
        }
    });

    std::cout << "Even count: " << evenCount << "\n";
    std::cout << "Sum of evens: " << evenSum << "\n";
    return 0;
}
