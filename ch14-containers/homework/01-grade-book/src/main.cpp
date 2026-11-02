#include <iomanip>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> scores;
    scores.push_back(72);
    scores.push_back(88);
    scores.push_back(95);
    scores.push_back(60);

    std::cout << "Count: " << scores.size() << "\n";

    int highest = scores[0];
    int lowest = scores[0];
    int total = 0;
    for (int score : scores) {
        if (score > highest) {
            highest = score;
        }
        if (score < lowest) {
            lowest = score;
        }
        total += score;
    }

    std::cout << "Highest: " << highest << "\n";
    std::cout << "Lowest: " << lowest << "\n";

    double average = static_cast<double>(total) / static_cast<double>(scores.size());
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average: " << average << "\n";

    return 0;
}
