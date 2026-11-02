#include <iostream>
#include <stdexcept>
#include <string>

// A guard announces when it's entered and when it's left. Its destructor runs at the end of any scope it's in.
class Guard {
public:
    Guard(std::string guardName) {
        name = guardName;
        std::cout << "Enter " << name << "\n";
    }

    ~Guard() {
        std::cout << "Leave " << name << "\n";
    }

private:
    std::string name;
};

void process(bool fail) {
    Guard section("section");
    std::cout << "Working\n";
    if (fail) {
        throw std::runtime_error("work failed");
    }
    std::cout << "Finished working\n";
}

int main() {
    try {
        process(false);
        process(true);
    } catch (const std::exception& error) {
        std::cout << "Caught: " << error.what() << "\n";
    }
    std::cout << "End\n";
    return 0;
}
