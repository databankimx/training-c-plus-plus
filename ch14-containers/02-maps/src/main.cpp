#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> counts;
    std::string words[] = {"apple", "pear", "apple", "fig", "pear", "apple"};

    for (const std::string& word : words) {
        counts[word]++;
    }

    for (const auto& entry : counts) {
        std::cout << entry.first << ": " << entry.second << "\n";
    }

    std::cout << "apple appears " << counts["apple"] << " times\n";

    if (counts.count("kiwi") == 0) {
        std::cout << "kiwi is not in the map\n";
    }

    // Try: change counts["apple"] to counts["kiwi"] in the second-to-last line. What does the map contain afterwards?
    return 0;
}
