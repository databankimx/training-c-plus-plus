#include <iostream>
#include <memory>
#include <string>

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
    std::shared_ptr<Resource> first = std::make_shared<Resource>("file D");
    std::cout << "Owners: " << first.use_count() << "\n";

    {
        // Copying a shared_ptr makes another owner of the same object. Both pointers refer to one Resource.
        std::shared_ptr<Resource> second = first;
        std::cout << "Owners: " << second.use_count() << "\n";
    }

    // The block has ended, so second has gone, and first is the only owner again.
    std::cout << "Owners: " << first.use_count() << "\n";
    std::cout << "End\n";

    // Try: copy first into a second shared_ptr, then reset first with first.reset(). Predict the owner count, and
    // whether file D is released at that point.
    return 0;
}
