#include <iostream>
#include <stacktrace>
#include <stdexcept>

// The innermost function. It captures the call stack at the point where the error happens, then throws.
void inner() {
    std::stacktrace trace = std::stacktrace::current();
    std::cout << "Frames captured: " << (trace.size() > 0 ? "yes" : "no") << "\n";
    throw std::runtime_error("inner failed");
}

void middle() {
    inner();
}

int main() {
    try {
        middle();
    } catch (const std::exception& error) {
        std::cout << "Caught: " << error.what() << "\n";
    }

    // Try: add a loop that prints trace[i].description() for each frame in trace. Predict the first name before you press Run.
    return 0;
}
