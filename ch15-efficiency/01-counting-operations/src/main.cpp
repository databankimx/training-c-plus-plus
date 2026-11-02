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

// Counts the work done by one loop over n items. Each pass counts as one operation.
long long linearOperations(int n) {
    long long count = 0;
    for (int i = 0; i < n; i++) {
        count++;
    }
    return count;
}

// Counts the work done by a loop nested inside another loop, each over n items.
long long quadraticOperations(int n) {
    long long count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            count++;
        }
    }
    return count;
}

int main() {
    int sizes[] = {10, 100, 1000};
    for (int n : sizes) {
        std::cout << "n = " << withCommas(n) << ": linear " << withCommas(linearOperations(n))
                  << ", quadratic " << withCommas(quadraticOperations(n)) << "\n";
    }

    // Try: add 10000 to the sizes array. Predict the quadratic count before you press Run.
    return 0;
}
