#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

void printFile(const std::string& name) {
    std::ifstream in(name);
    if (!in) {
        throw std::runtime_error("could not open " + name);
    }

    std::string line;
    while (std::getline(in, line)) {
        std::cout << line << "\n";
    }
}

int main() {
    try {
        printFile("data/settings.txt");
    } catch (const std::exception& error) {
        std::cout << error.what() << "\n";
    }

    return 0;
}
