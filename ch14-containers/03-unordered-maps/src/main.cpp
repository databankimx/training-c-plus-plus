#include <iostream>
#include <string>
#include <unordered_map>

int main() {
    std::unordered_map<std::string, int> counts;
    std::string words[] = {"apple", "pear", "apple", "fig", "pear", "apple"};

    for (const std::string& word : words) {
        counts[word]++;
    }

    std::cout << "Distinct words: " << counts.size() << "\n";
    std::cout << "apple: " << counts["apple"] << "\n";
    std::cout << "pear: " << counts["pear"] << "\n";
    std::cout << "fig: " << counts["fig"] << "\n";

    if (counts.count("kiwi") == 0) {
        std::cout << "kiwi is not in the map\n";
    }

    // Try: add a loop that prints every entry. Run it twice, then predict whether the order can change.
    return 0;
}
