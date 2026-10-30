#include <iostream>
#include <thread>

// Adds the numbers from first up to, but not including, last. The result goes into total, which only this thread writes.
void sumRange(int first, int last, long long& total) {
    long long sum = 0;
    for (int i = first; i < last; i++) {
        sum += i;
    }
    total = sum;
}

int main() {
    long long firstHalf = 0;
    long long secondHalf = 0;

    std::thread first(sumRange, 1, 501, std::ref(firstHalf));
    std::thread second(sumRange, 501, 1001, std::ref(secondHalf));
    first.join();
    second.join();

    std::cout << "Sum: " << firstHalf + secondHalf << "\n";
    return 0;
}
