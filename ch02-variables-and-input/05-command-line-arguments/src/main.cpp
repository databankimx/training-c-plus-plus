#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    // argc counts every word on the command line, including the program's own name. argv[0] is that name,
    // so the first real argument is argv[1].
    std::cout << "Arguments received: " << argc - 1 << "\n";
    for (int i = 1; i < argc; i++) {
        std::cout << "Argument " << i << ": " << argv[i] << "\n";
    }

    // Two numbers, given on the command line, are added. The text is converted with std::stoi.
    if (argc == 3) {
        const int first = std::stoi(argv[1]);
        const int second = std::stoi(argv[2]);
        std::cout << first << " + " << second << " = " << first + second << "\n";
    } else {
        std::cout << "Give two numbers, for example: program 4 9\n";
    }

    // Try: run with the arguments 4 nine, and predict what happens. Then run with no arguments at all.
    return 0;
}
