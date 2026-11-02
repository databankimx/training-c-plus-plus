#include <iostream>
#include <string>

// A class template. Box<int>, Box<std::string>, and any other Box are generated from this one definition.
template <typename T>
class Box {
public:
    Box(T value) {
        item = value;
    }

    T get() const {
        return item;
    }

    void set(T value) {
        item = value;
    }

private:
    T item;
};

int main() {
    Box<int> number(42);
    Box<std::string> word("hello");

    std::cout << number.get() << "\n";
    number.set(7);
    std::cout << number.get() << "\n";
    std::cout << word.get() << "\n";

    // Try: create a Box<double> holding 2.5, and call set with 4. Predict the value get returns, and whether the
    // int 4 is accepted.
    return 0;
}
