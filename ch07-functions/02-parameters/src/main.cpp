#include <iostream>
#include <string>

// fname and age are parameters. The values passed in when the function is called are its arguments.
void introduce(std::string fname, int age) {
    std::cout << fname << " is " << age << " years old.\n";
}

// A default value makes the argument optional. This one is used when the caller passes nothing.
void welcome(std::string country = "United States") {
    std::cout << "The country is: " << country << "\n";
}

int main() {
    introduce("Scott", 53);
    welcome();
    welcome("Mexico");

    // Try: call introduce with its arguments in the other order, as introduce(53, "Scott"). What does the compiler say?
    return 0;
}
