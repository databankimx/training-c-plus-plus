#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> counts = {{"pear", 5}, {"apple", 3}, {"fig", 2}};

    for (const auto& [word, count] : counts) {
        std::cout << word << " " << count << "\n";
    }

    int total = 0;
    for (const auto& [word, count] : counts) {
        total += count;
    }
    std::cout << "Total: " << total << "\n";
    return 0;
}
