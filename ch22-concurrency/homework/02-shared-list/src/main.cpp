#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

// Adds the numbers from first up to, but not including, last to the shared list. Each push_back happens while the
// lock is held.
void addValues(std::vector<int>& list, std::mutex& lock, int first, int last) {
    for (int value = first; value < last; value++) {
        std::lock_guard<std::mutex> guard(lock);
        list.push_back(value);
    }
}

int main() {
    std::vector<int> list;
    std::mutex lock;

    std::thread first(addValues, std::ref(list), std::ref(lock), 1, 6);
    std::thread second(addValues, std::ref(list), std::ref(lock), 6, 11);
    first.join();
    second.join();

    long long sum = 0;
    for (int value : list) {
        sum += value;
    }

    std::cout << "Size: " << list.size() << "\n";
    std::cout << "Sum: " << sum << "\n";
    return 0;
}
