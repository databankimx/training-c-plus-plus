#include <iostream>
#include <memory>
#include <string>

// A resource that announces when it's acquired and released, as in the previous step.
class Resource {
public:
    Resource(std::string resourceName) {
        name = resourceName;
        std::cout << "Acquire " << name << "\n";
    }

    ~Resource() {
        std::cout << "Release " << name << "\n";
    }

    void describe() const {
        std::cout << "Holding " << name << "\n";
    }

private:
    std::string name;
};

int main() {
    std::cout << "Start\n";

    {
        // The unique_ptr owns the Resource. When it goes out of scope, it deletes the Resource, and that calls
        // the Resource's destructor.
        std::unique_ptr<Resource> owner = std::make_unique<Resource>("file C");
        owner->describe();
        std::cout << "Using file C\n";
    }

    std::cout << "After the block\n";

    // Try: copy the unique_ptr with std::unique_ptr<Resource> copy = owner; inside the block. Predict the error.
    return 0;
}
