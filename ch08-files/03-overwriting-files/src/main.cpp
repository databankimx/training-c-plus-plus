#include <fstream>
#include <iostream>
#include <string>

int main() {
    // The block ends, so out goes out of scope and the file closes automatically.
    {
        std::ofstream out("data/test.txt");
        out << "This first version of the text is quite long.";
    }

    // fstream opens the existing file without clearing it, so this text overwrites only its first part.
    std::fstream file("data/test.txt");
    file << "Short text.";
    file.close();

    std::ifstream in("data/test.txt");
    std::string line;
    while (std::getline(in, line)) {
        std::cout << line << "\n";
    }

    // Try: change std::fstream to std::ofstream, and predict the output before you press Run.
    return 0;
}
