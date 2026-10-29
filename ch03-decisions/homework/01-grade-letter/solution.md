## Solution: Grade letter

The example uses a `char` to hold the grade, starting with `'F'`. The chain checks the bands from the top down. A score of 95 passes the first test, so it becomes `A`, and the other tests are skipped. A score of 85 fails the first test, passes the second, and becomes `B`.

Because the chain is ordered, each test only needs the lower bound of its band. When the code reaches `score >= 80`, we already know the score is below 90, so there's no need to say so. That's the reason the order matters.

Starting with `'F'` covers the last band without a test. Any score below 60 never matches a condition, so it keeps the value it started with.

The boundary values are where the mistakes happen. Check 90, 80, 70, and 60 by hand, since each one should land in the higher band.
