#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::ifstream in("data/input.txt");
    if (!in) {
        std::cout << "Could not open data/input.txt\n";
        return 1;
    }

    std::ofstream out("data/numbered.txt");
    if (!out) {
        std::cout << "Could not create data/numbered.txt\n";
        return 1;
    }

    std::string line;
    int count = 0;
    while (std::getline(in, line)) {
        count++;
        out << count << ". " << line << "\n";
    }

    in.close();
    out.close();
    std::cout << "Wrote " << count << " lines to data/numbered.txt\n";
    return 0;
}
