#include <cstddef>
#include <iostream>
#include <string>

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

// Counts the pairs (i, j) with i < j, using nested loops. The inner loop starts one place after the outer one.
int countPairs(int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            count++;
        }
    }
    return count;
}

// The same count, worked out directly: n items give n times (n - 1) divided by 2 pairs.
int pairFormula(int n) {
    return n * (n - 1) / 2;
}

int main() {
    int sizes[] = {4, 10, 100};
    for (int n : sizes) {
        std::cout << "n = " << n << ": pairs " << withCommas(countPairs(n))
                  << ", formula " << withCommas(pairFormula(n)) << "\n";
    }
    return 0;
}
