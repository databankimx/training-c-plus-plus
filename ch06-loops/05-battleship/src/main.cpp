#include <iostream>

int main() {
    // A 1 marks a square with a ship, and a 0 marks water. A hit sets its square back to 0.
    int ships[4][4] = {
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0}
    };

    int hits = 0;
    int turns = 0;

    while (hits < 4) {
        int row = 0;
        int column = 0;

        std::cout << "Selecting coordinates (type q to quit)\n";
        std::cout << "Choose a row number between 0 and 3: " << std::flush;
        if (!(std::cin >> row)) {
            char word = ' ';
            std::cin.clear();
            std::cin >> word;
            if (word == 'q' || word == 'Q') {
                break;
            }
            std::cin.ignore(10000, '\n');
            std::cout << "Please enter a number.\n\n";
            continue;
        }

        std::cout << "Choose a column number between 0 and 3: " << std::flush;
        if (!(std::cin >> column)) {
            char word = ' ';
            std::cin.clear();
            std::cin >> word;
            if (word == 'q' || word == 'Q') {
                break;
            }
            std::cin.ignore(10000, '\n');
            std::cout << "Please enter a number.\n\n";
            continue;
        }

        if (row < 0 || row > 3 || column < 0 || column > 3) {
            std::cout << "Please choose numbers from 0 to 3.\n\n";
            continue;
        }

        if (ships[row][column] == 1) {
            ships[row][column] = 0;
            hits++;
            std::cout << "Hit! " << (4 - hits) << " left.\n\n";
        } else {
            std::cout << "Miss\n\n";
        }

        turns++;
    }

    if (hits == 4) {
        std::cout << "Victory!\n";
        std::cout << "You won in " << turns << " turns\n";
    } else {
        std::cout << "You quit with " << (4 - hits) << " ships left.\n";
    }

    // Try: move one ship by changing the grid. Predict whether the game still ends after four hits.
    return 0;
}
