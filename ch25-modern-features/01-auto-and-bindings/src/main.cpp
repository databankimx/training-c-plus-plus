#include <iostream>
#include <map>
#include <string>
#include <utility>

int main() {
    // auto takes the type from the value on the right, so the type is written once, or not at all.
    std::map<std::string, int> scores = {{"Ada", 91}, {"Grace", 88}};

    // A structured binding unpacks each element of the map into two named variables, name and score.
    for (const auto& [name, score] : scores) {
        std::cout << name << ": " << score << "\n";
    }

    // The same unpacking works on a pair, which holds two values of different types.
    auto [count, average] = std::pair{3, 4.5};
    std::cout << count << " " << average << "\n";

    // Try: add {"Linus", 95} to the map, and predict the order the loop prints the names in, before you press Run.
    return 0;
}
