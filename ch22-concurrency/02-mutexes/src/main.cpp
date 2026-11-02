#include <iostream>
#include <mutex>
#include <thread>

// Adds one to total, the given number of times. The mutex is locked for each addition, so two threads never change
// total at the same moment.
void addMany(int& total, std::mutex& lock, int times) {
    for (int i = 0; i < times; i++) {
        std::lock_guard<std::mutex> guard(lock);   // locked here, and unlocked when guard goes out of scope
        total++;
    }
}

int main() {
    int total = 0;
    std::mutex lock;

    // std::ref passes a reference through the thread's arguments, so both threads change the same total.
    std::thread first(addMany, std::ref(total), std::ref(lock), 100000);
    std::thread second(addMany, std::ref(total), std::ref(lock), 100000);
    first.join();
    second.join();

    std::cout << "Total: " << total << "\n";

    // Try: remove the lock_guard line from addMany, and run the program several times. Predict whether the total is
    // always 200000, and explain what the lock prevents.
    return 0;
}
