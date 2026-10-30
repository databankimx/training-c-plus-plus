#include <fstream>
#include <iostream>

int main() {
    std::ofstream out("data/greetings.txt");
    if (!out) {
        std::cout << "Could not create the file.\n";
        return 1;
    }

    out << "Hello, file!\n";
    out << "Writing to a file works like cout.\n";
    out.close();

    std::cout << "Wrote data/greetings.txt\n";
    return 0;
}
