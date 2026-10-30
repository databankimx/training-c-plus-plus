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

private:
    std::string name;
};

int main() {
    std::cout << "Start\n";

    std::unique_ptr<Resource> a = std::make_unique<Resource>("file E");

    // A unique_ptr can't be copied, so the only way to give the object to b is to move it. Afterward, a is empty.
    std::unique_ptr<Resource> b = std::move(a);

    std::cout << "a owns nothing: " << (a ? "no" : "yes") << "\n";
    std::cout << "b owns the resource: " << (b ? "yes" : "no") << "\n";
    std::cout << "End\n";

    // Try: call std::unique_ptr<Resource> c = a; instead of the move, and predict the error before you press Run.
    return 0;
}
