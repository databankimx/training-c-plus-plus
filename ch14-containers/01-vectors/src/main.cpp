#include <iostream>
#include <stdexcept>
#include <vector>

int main() {
    std::vector<int> scores;
    scores.push_back(72);
    scores.push_back(88);
    scores.push_back(95);

    std::cout << "Count: " << scores.size() << "\n";
    std::cout << "First: " << scores[0] << "\n";
    std::cout << "Last: " << scores.at(scores.size() - 1) << "\n";

    int total = 0;
    for (int score : scores) {
        total += score;
    }
    std::cout << "Total: " << total << "\n";
    std::cout << "Average: " << total / static_cast<int>(scores.size()) << "\n";

    scores.push_back(60);
    std::cout << "After adding: " << scores.size() << "\n";

    try {
        std::cout << scores.at(10) << "\n";
    } catch (const std::out_of_range&) {
        std::cout << "Index 10 is out of range.\n";
    }

    std::vector<int> stack = {1, 2, 3};
    std::cout << "Empty: " << (stack.empty() ? "yes" : "no") << "\n";
    std::cout << "Front: " << stack.front() << ", back: " << stack.back() << "\n";

    stack.pop_back();
    std::cout << "After pop_back: size " << stack.size() << ", back " << stack.back() << "\n";

    stack.insert(stack.begin() + 1, 99);
    stack.erase(stack.begin());
    std::cout << "Elements:";
    for (int value : stack) {
        std::cout << " " << value;
    }
    std::cout << "\n";

    stack.clear();
    std::cout << "Empty after clear: " << (stack.empty() ? "yes" : "no") << "\n";

    std::vector<int> reserved;
    reserved.reserve(10);
    std::cout << "Size " << reserved.size() << ", capacity at least 10: "
              << (reserved.capacity() >= 10 ? "yes" : "no") << "\n";

    // Try: change insert to insert at stack.begin(). Predict the Elements line before you press Run.
    return 0;
}
