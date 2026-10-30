#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

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
    std::unique_ptr<Resource> p = std::make_unique<Resource>("vessel");

    std::vector<std::unique_ptr<Resource>> holders;
    holders.push_back(std::move(p));
    std::cout << "Size after push: " << holders.size() << "\n";
    std::cout << "p owns nothing: " << (p ? "no" : "yes") << "\n";

    std::unique_ptr<Resource> back = std::move(holders[0]);
    holders.pop_back();
    std::cout << "Got back: " << (back ? "yes" : "no") << "\n";

    std::cout << "End\n";
    return 0;
}
