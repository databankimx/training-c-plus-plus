// Diagnostics test 1: can std::stacktrace show the function names where an exception was thrown?
// The exception captures its stack at construction, which is where the throw happens, and the catch block prints it.
// Expected output: the text "Caught: boom from level3", then a trace that includes level3, level2, and level1.

#include <iostream>
#include <stacktrace>
#include <stdexcept>
#include <string>

struct TracedError : std::runtime_error {
    std::stacktrace where;
    explicit TracedError(const char* message)
        : std::runtime_error(message), where(std::stacktrace::current()) {}
};

void level3() {
    throw TracedError("boom from level3");
}

void level2() {
    level3();
}

void level1() {
    level2();
}

int main() {
    try {
        level1();
    } catch (const TracedError& error) {
        std::cout << "Caught: " << error.what() << "\n";
        std::cout << "Trace from the throw site:\n" << std::to_string(error.where) << "\n";
    }
    return 0;
}
