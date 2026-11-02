#include <iostream>
#include <string>

// A year is a leap year when it's divisible by 4, except that a year divisible by 100 is not, unless it's also
// divisible by 400.
bool isLeapYear(int year) {
    if (year % 400 == 0) {
        return true;
    }
    if (year % 100 == 0) {
        return false;
    }
    return year % 4 == 0;
}

void check(bool passed, const std::string& name, int& failures) {
    if (passed) {
        std::cout << "PASS " << name << "\n";
    } else {
        std::cout << "FAIL " << name << "\n";
        failures++;
    }
}

int main() {
    int failures = 0;

    check(isLeapYear(2024), "2024 is a leap year", failures);
    check(!isLeapYear(1900), "1900 is not a leap year", failures);
    check(isLeapYear(2000), "2000 is a leap year", failures);
    check(!isLeapYear(2023), "2023 is not a leap year", failures);

    std::cout << "Failures: " << failures << "\n";
    return failures == 0 ? 0 : 1;
}
