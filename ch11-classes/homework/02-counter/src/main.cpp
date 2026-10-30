#include <iostream>

class Counter {
public:
    Counter(int start = 0) {
        count = start;
    }

    void increment() {
        count++;
    }

    void reset() {
        count = 0;
    }

    int value() const {
        return count;
    }

private:
    int count = 0;
};

int main() {
    Counter c;
    c.increment();
    c.increment();
    c.increment();
    std::cout << "Count: " << c.value() << "\n";

    c.reset();
    std::cout << "Count: " << c.value() << "\n";

    Counter d(10);
    d.increment();
    std::cout << "Count: " << d.value() << "\n";

    return 0;
}
