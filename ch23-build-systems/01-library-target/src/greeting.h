#ifndef GREETING_H
#define GREETING_H

#include <string>

// Returns a greeting for the name. The definition is in greeting.cpp, which is compiled into a library.
std::string makeGreeting(const std::string& name);

#endif
