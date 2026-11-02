#include <iostream>
#include <memory>
#include <string>
#include <utility>

// A resource that announces when it's acquired and released.
class Resource {
public:
    Resource(std::string resourceName) {
        name = resourceName;
        std::cout << "Acquire " << name << "\n";
    }

    ~Resource() {
        std::cout << "Release " << name << "\n";
    }

    std::string getName() const {
        return name;
    }

private:
    std::string name;
};

// The function takes ownership of the resource. The resource is released when the function returns.
void consume(std::unique_ptr<Resource> resource) {
    std::cout << "Received " << resource->getName() << "\n";
}

int main() {
    std::unique_ptr<Resource> handoff = std::make_unique<Resource>("handoff");

    consume(std::move(handoff));
    std::cout << "Back in main\n";

    std::cout << "End\n";
    return 0;
}
