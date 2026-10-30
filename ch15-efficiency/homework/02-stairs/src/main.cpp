#include <iostream>
#include <map>
#include <stdexcept>

// The helper does the recursion, counting its calls. Its inputs are always valid, so it doesn't check them.
long long waysNaiveHelper(int n, long long& calls) {
    calls++;
    if (n < 2) {
        return 1;
    }
    return waysNaiveHelper(n - 1, calls) + waysNaiveHelper(n - 2, calls);
}

// The public function checks the input once, then starts the recursion.
long long waysNaive(int n, long long& calls) {
    if (n < 0) {
        throw std::invalid_argument("n must not be negative");
    }
    return waysNaiveHelper(n, calls);
}

// The helper does the memoized recursion. It assumes n is valid, and it reuses stored answers.
long long waysMemoHelper(int n, std::map<int, long long>& memo, long long& calls) {
    calls++;
    if (n < 2) {
        return 1;
    }
    if (memo.count(n) > 0) {
        return memo[n];
    }
    long long result = waysMemoHelper(n - 1, memo, calls) + waysMemoHelper(n - 2, memo, calls);
    memo[n] = result;
    return result;
}

// The public function checks the input once, then starts the memoized recursion.
long long waysMemo(int n, std::map<int, long long>& memo, long long& calls) {
    if (n < 0) {
        throw std::invalid_argument("n must not be negative");
    }
    return waysMemoHelper(n, memo, calls);
}

int main() {
    int sizes[] = {5, 10};
    for (int n : sizes) {
        long long naiveCalls = 0;
        long long naiveWays = waysNaive(n, naiveCalls);

        std::map<int, long long> memo;
        long long memoCalls = 0;
        long long memoWays = waysMemo(n, memo, memoCalls);

        std::cout << "n = " << n << ": ways " << naiveWays
                  << ", naive calls " << naiveCalls
                  << ", memoized calls " << memoCalls << "\n";
        if (naiveWays != memoWays) {
            std::cout << "The two versions disagree.\n";
        }
    }
    return 0;
}
