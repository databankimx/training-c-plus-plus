#include <iostream>
#include <optional>
#include <vector>

// Returns the index of target in values, or nothing when target isn't there.
std::optional<int> findIndex(const std::vector<int>& values, int target) {
    for (int i = 0; i < static_cast<int>(values.size()); i++) {
        if (values[static_cast<std::size_t>(i)] == target) {
            return i;
        }
    }
    return std::nullopt;
}

int main() {
    std::vector<int> values = {4, 8, 15};

    std::optional<int> found = findIndex(values, 8);
    if (found) {
        std::cout << "Found at " << *found << "\n";
    }

    std::optional<int> missing = findIndex(values, 99);
    std::cout << (missing.has_value() ? "Found" : "Not found") << "\n";

    // value_or gives a fallback when there is no value, so the caller never reads an empty optional.
    std::cout << missing.value_or(-1) << "\n";

    // Try: call findIndex(values, 4) and print it with value_or(-1). Predict the output before you press Run.
    return 0;
}
