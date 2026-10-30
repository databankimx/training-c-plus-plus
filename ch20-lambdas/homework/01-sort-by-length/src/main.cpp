#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> words = {"pear", "fig", "banana", "kiwi"};

    // stable_sort keeps values that compare as equal in their original order, so pear stays before kiwi.
    std::stable_sort(words.begin(), words.end(),
                     [](const std::string& a, const std::string& b) { return a.size() < b.size(); });

    std::cout << "By length:";
    for (const std::string& word : words) {
        std::cout << " " << word;
    }
    std::cout << "\n";
    return 0;
}
