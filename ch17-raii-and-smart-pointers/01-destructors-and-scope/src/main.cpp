#include <iostream>
#include <string>

// A resource that announces when it's acquired and when it's released. The release happens in the destructor.
class Resource {
public:
    Resource(std::string resourceName) {
        name = resourceName;
        std::cout << "Acquire " << name << "\n";
    }

    // The destructor has the class's name with a tilde in front. It runs when the object's scope ends.
    ~Resource() {
        std::cout << "Release " << name << "\n";
    }

private:
    std::string name;
};

void useResource() {
    Resource first("file A");
    std::cout << "Using file A\n";
}   // first is destroyed here, when the function returns

int main() {
    std::cout << "Start\n";

    {
        Resource second("file B");
        std::cout << "Using file B\n";
    }   // second is destroyed here, at the end of its block

    useResource();

    std::cout << "End\n";

    // Try: add a second Resource named "file C" in main, after "End". Predict the order its messages print in,
    // compared with file A's.
    return 0;
}
