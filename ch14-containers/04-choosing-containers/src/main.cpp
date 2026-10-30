#include <iostream>
#include <map>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> names = {"Ada", "Grace", "Alan"};
    std::cout << "Names: " << names.size() << "\n";

    std::map<std::string, int> lengths;
    for (const std::string& name : names) {
        lengths[name] = static_cast<int>(name.size());
    }

    for (const auto& entry : lengths) {
        std::cout << entry.first << ": " << entry.second << "\n";
    }

    // Try: add "Ada" a second time to the vector. Predict how many entries the map holds afterwards.
    return 0;
}
