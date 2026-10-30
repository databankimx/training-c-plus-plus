## Solution: Grade book

The highest and lowest start at the first score, `scores[0]`. Starting from a real value, rather than zero, matters: a grade book where every score is above zero would report a lowest of zero if the search began there.

The one loop finds both the highest and lowest, and adds the total. Each `if` compares the current score with the running value, so a single pass does all three jobs. A loop per statistic would also work, but it reads the vector three times for no gain.

The average needs both numbers as `double`. `static_cast<double>(total)` converts the sum before the division, so the division keeps its fraction. Converting only one side is enough, but converting both states the intent clearly.

The `fixed` and `setprecision` settings come after the three integer lines, so those lines print as whole numbers, and only the average is formatted to two places.
