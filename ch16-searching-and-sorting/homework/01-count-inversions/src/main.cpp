#include <cstddef>
#include <iostream>
#include <vector>

// Counts pairs (i, j) with i < j and values[i] > values[j], by checking every pair.
long long countInversions(const std::vector<int>& values) {
    long long count = 0;
    for (std::size_t i = 0; i < values.size(); i++) {
        for (std::size_t j = i + 1; j < values.size(); j++) {
            if (values[i] > values[j]) {
                count++;
            }
        }
    }
    return count;
}

// Insertion sort, counting how many times a value moves one place left. The list is taken by value, so the caller's
// list is not changed.
long long insertionMoves(std::vector<int> values) {
    long long moves = 0;
    for (std::size_t i = 1; i < values.size(); i++) {
        std::size_t j = i;
        while (j > 0 && values[j - 1] > values[j]) {
            int temp = values[j - 1];
            values[j - 1] = values[j];
            values[j] = temp;
            moves++;
            j--;
        }
    }
    return moves;
}

int main() {
    std::vector<int> list = {5, 1, 4, 2, 3};
    long long inversions = countInversions(list);
    long long moves = insertionMoves(list);

    std::cout << "Inversions: " << inversions << "\n";
    std::cout << "Insertion sort moves: " << moves << "\n";
    std::cout << "Match: " << (inversions == moves ? "yes" : "no") << "\n";

    // Try: change the list to {1, 2, 3, 4, 5}. Predict both numbers before you press Run.
    return 0;
}
