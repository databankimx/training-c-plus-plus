## Solution: Times table

The loop counts from 1 to 10 with `i <= 10`. The `<=` is what makes the table reach 10. Writing `i < 10` would stop at 9, and the last line would be missing, which is the mistake the lesson asks you to look for.

Each line prints the number, the counter, and the product. The product is calculated inside the `cout` statement, so there's no separate variable for it. That's fine for a single use, and it keeps the loop short.

The loop runs exactly ten times for every input, including 0, since its count doesn't depend on the number the user enters. The number only changes the products.

For the first extension, put a `break` after the product is printed, with an `if` that tests for a product above 50. Printing before the test shows the line that passes 50, and testing first would hide it. Decide which behavior the exercise asks for, and be ready to say why.
