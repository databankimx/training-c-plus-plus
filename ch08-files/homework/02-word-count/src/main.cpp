#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::ifstream lineFile("data/essay.txt");
    if (!lineFile) {
        std::cout << "Could not open data/essay.txt\n";
        return 1;
    }
    std::string line;
    int lines = 0;
    while (std::getline(lineFile, line)) {
        lines++;
    }
    lineFile.close();

    std::ifstream wordFile("data/essay.txt");
    if (!wordFile) {
        std::cout << "Could not open data/essay.txt\n";
        return 1;
    }
    std::string word;
    int words = 0;
    while (wordFile >> word) {
        words++;
    }
    wordFile.close();

    std::cout << "Lines: " << lines << "\n";
    std::cout << "Words: " << words << "\n";
    return 0;
}
