#include <cstddef>
#include <iostream>
#include <map>
#include <stdexcept>
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

// The helper does the naive recursion. Its inputs are always valid, so it doesn't check them.
long long fibNaiveHelper(int n, long long& calls) {
    calls++;
    if (n < 2) {
        return n;
    }
    return fibNaiveHelper(n - 1, calls) + fibNaiveHelper(n - 2, calls);
}

// The public function checks the input once, then starts the recursion.
long long fibNaive(int n, long long& calls) {
    if (n < 0) {
        throw std::invalid_argument("n must not be negative");
    }
    return fibNaiveHelper(n, calls);
}

// The loop has no recursion, so the single check at the top is all it needs.
long long fibLoop(int n) {
    if (n < 0) {
        throw std::invalid_argument("n must not be negative");
    }
    long long a = 0;
    long long b = 1;
    for (int i = 0; i < n; i++) {
        long long next = a + b;
        a = b;
        b = next;
    }
    return a;
}

// The helper does the memoized recursion. It assumes n is valid, and it uses the map to reuse answers.
long long fibMemoHelper(int n, std::map<int, long long>& memo, long long& calls) {
    calls++;
    if (n < 2) {
        return n;
    }
    if (memo.count(n) > 0) {
        return memo[n];
    }
    long long result = fibMemoHelper(n - 1, memo, calls) + fibMemoHelper(n - 2, memo, calls);
    memo[n] = result;
    return result;
}

// The public function checks the input once, then starts the memoized recursion.
long long fibMemo(int n, std::map<int, long long>& memo, long long& calls) {
    if (n < 0) {
        throw std::invalid_argument("n must not be negative");
    }
    return fibMemoHelper(n, memo, calls);
}

int main() {
    int sizes[] = {10, 20, 30};
    for (int n : sizes) {
        long long naiveCalls = 0;
        long long naiveValue = fibNaive(n, naiveCalls);

        std::map<int, long long> memo;
        long long memoCalls = 0;
        long long memoValue = fibMemo(n, memo, memoCalls);

        std::cout << "n = " << n << ": value " << withCommas(naiveValue)
                  << ", naive calls " << withCommas(naiveCalls)
                  << ", memoized calls " << withCommas(memoCalls) << "\n";

        if (naiveValue != memoValue || naiveValue != fibLoop(n)) {
            std::cout << "The three versions disagree.\n";
        }
    }

    // A negative n is refused with an exception, so the program reports the problem instead of recursing.
    long long refusedCalls = 0;
    try {
        fibNaive(-1, refusedCalls);
    } catch (const std::invalid_argument& error) {
        std::cout << "n = -1 refused: " << error.what() << "\n";
    }

    // Try: change -1 to -5. Predict whether the message changes, and whether any calls are counted.
    return 0;
}
