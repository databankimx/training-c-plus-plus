#include <iostream>
#include <string>

// A pair of values whose types are chosen by the caller.
template <typename First, typename Second>
class Pair {
public:
    Pair(First firstValue, Second secondValue) {
        first = firstValue;
        second = secondValue;
    }

    First getFirst() const {
        return first;
    }

    Second getSecond() const {
        return second;
    }

private:
    First first;
    Second second;
};

int main() {
    Pair<int, std::string> count(3, "three");
    std::cout << "Pair: " << count.getFirst() << " " << count.getSecond() << "\n";

    Pair<std::string, double> constant("pi", 3.14);
    std::cout << "Pair: " << constant.getFirst() << " " << constant.getSecond() << "\n";
    return 0;
}
