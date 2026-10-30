#include <iostream>
#include <string>

// Counts the lowercase vowels a, e, i, o, and u in a word.
int countVowels(const std::string& word) {
    int count = 0;
    for (char c : word) {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
    }
    return count;
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

    check(countVowels("hello") == 2, "hello has 2 vowels", failures);
    check(countVowels("") == 0, "an empty word has no vowels", failures);
    check(countVowels("rhythm") == 0, "rhythm has no vowels", failures);
    check(countVowels("education") == 5, "education has 5 vowels", failures);

    std::cout << "Failures: " << failures << "\n";
    return failures == 0 ? 0 : 1;
}
