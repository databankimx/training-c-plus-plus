#include <cctype>
#include <iostream>
#include <string>

struct Contact {
    std::string name;
    std::string phone;
};

// Returns a lowercase copy of the text, so comparisons ignore letter case.
std::string lowercase(std::string text) {
    for (char& c : text) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return text;
}

int main() {
    Contact contacts[3] = {
        {"Ada", "555-0101"},
        {"Grace", "555-0102"},
        {"Alan", "555-0103"},
    };

    std::cout << "Enter a name: " << std::flush;
    std::string wanted;
    std::getline(std::cin, wanted);

    bool found = false;
    for (int i = 0; i < 3; i++) {
        if (lowercase(contacts[i].name) == lowercase(wanted)) {
            std::cout << contacts[i].name << ": " << contacts[i].phone << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "No contact named " << wanted << ".\n";
    }

    return 0;
}
