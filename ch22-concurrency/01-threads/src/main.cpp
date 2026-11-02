#include <iostream>
#include <string>
#include <thread>

// The work the new thread does. It runs at the same time as the thread that started it.
void greet(std::string name) {
    std::cout << "Hello from " << name << "\n";
}

int main() {
    std::cout << "Start\n";

    // Starting the thread runs greet on a second thread. join waits until that thread has finished.
    std::thread worker(greet, "worker");
    worker.join();

    std::cout << "After join\n";

    // Try: remove the join call, and add a second thread. Predict whether the output is always in the same order.
    return 0;
}
