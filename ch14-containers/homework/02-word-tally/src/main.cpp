#include <iostream>
#include <map>
#include <string>

int main() {
    std::string words[] = {"red", "blue", "red", "green", "blue", "red"};

    std::map<std::string, int> counts;
    for (const std::string& word : words) {
        counts[word]++;
    }

    for (const auto& entry : counts) {
        std::cout << entry.first << ": " << entry.second << "\n";
    }

    std::string bestWord;
    int bestCount = 0;
    for (const auto& entry : counts) {
        if (entry.second > bestCount) {
            bestCount = entry.second;
            bestWord = entry.first;
        }
    }

    std::cout << "Most common: " << bestWord << "\n";
    return 0;
}
