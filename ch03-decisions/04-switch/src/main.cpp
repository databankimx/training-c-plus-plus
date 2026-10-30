#include <iostream>

int main() {
    int day = 3;
    switch (day) {
        case 1:
            std::cout << "Monday\n";
            break;
        case 2:
            std::cout << "Tuesday\n";
            break;
        case 3:
            std::cout << "Wednesday\n";
            break;
        case 4:
            std::cout << "Thursday\n";
            break;
        case 5:
            std::cout << "Friday\n";
            break;
        default:
            std::cout << "Not a workday\n";
            break;
    }

    char grade = 'B';
    switch (grade) {
        case 'A':
            std::cout << "Excellent\n";
            break;
        case 'B':
        case 'C':
            std::cout << "Good\n";
            break;
        default:
            std::cout << "Keep going\n";
            break;
    }

    int level = 1;
    switch (level) {
        case 1:
            std::cout << "Level 1 tasks\n";
            [[fallthrough]];
        case 2:
            std::cout << "Level 2 tasks\n";
            break;
    }

    // Try: change level to 2. Predict how many lines the last switch prints.
    return 0;
}
