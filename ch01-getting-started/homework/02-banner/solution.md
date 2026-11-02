## Solution: A banner

The example prints three lines, one per `std::cout` statement, and each ends with `\n`.

The part that needs care is the widths. Count the characters in the middle line: the stars, a space, the five letters and punctuation of `Hello!`, another space, and the stars again. That's ten characters in total, so the top and bottom lines need exactly ten stars each.

For the extension, you'd need a variable for the greeting and a loop to print the stars, which is later in the course. Until then, typing the stars out is perfectly fine. Counting them carefully is the lesson.
