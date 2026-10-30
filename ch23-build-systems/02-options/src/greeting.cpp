#include "greeting.h"

#include <cctype>

std::string makeGreeting(const std::string& name) {
    std::string text = "Hello, " + name + "!";
#ifdef LOUD_GREETINGS
    for (char& c : text) {
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }
#endif
    return text;
}
