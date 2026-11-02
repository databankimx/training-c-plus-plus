#include <iostream>
#include <memory>
#include <string>
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
    std::shared_ptr<Resource> original = std::make_shared<Resource>("shared");
    std::vector<std::shared_ptr<Resource>> holders;

    holders.push_back(original);
    std::cout << "Owners: " << original.use_count() << "\n";

    holders.push_back(original);
    std::cout << "Owners: " << original.use_count() << "\n";

    holders.clear();
    std::cout << "Owners: " << original.use_count() << "\n";

    std::cout << "End\n";
    return 0;
}
