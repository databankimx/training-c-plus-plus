## Solution: Highest score

The example stores each score in its own element, reading straight into `scores[0]`, `scores[1]`, and `scores[2]`. The highest value starts as the first score, and each later score replaces it only when it's larger.

Two `if` blocks are enough, because the comparison always uses the same running value. Each `if` is independent of the other, so both run, whatever the first found. That matches the choice the decisions chapter discussed.

The tie case works without any special handling. A score equal to the current highest doesn't pass `>`, so the highest stays the same, and the printed value is still correct. The program only needs a strict "greater than" test, not an equality test.

Once the loops chapter arrives, the same three comparisons can be written as a loop over the array. For now, the explicit version shows exactly what the loop will do on each pass.
