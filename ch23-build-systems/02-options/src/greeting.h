#ifndef GREETING_H
#define GREETING_H

#include <string>

// Returns a greeting for the name. When the build sets LOUD_GREETINGS, the greeting is in capitals.
std::string makeGreeting(const std::string& name);

#endif
