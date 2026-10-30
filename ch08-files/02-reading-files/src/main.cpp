#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::ifstream in("data/notes.txt");
    if (!in) {
        std::cout << "Could not open data/notes.txt\n";
        return 1;
    }

    std::string line;
    int count = 0;
    while (std::getline(in, line)) {
        count++;
        std::cout << count << ": " << line << "\n";
    }

    in.close();
    std::cout << "Lines read: " << count << "\n";
    return 0;
}
