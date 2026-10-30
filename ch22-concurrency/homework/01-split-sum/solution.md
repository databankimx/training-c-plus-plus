## Solution: Split sum

The sum of 1 through 500 is 125,250, and the sum of 501 through 1,000 is 375,250. Their total is 500,500, which the formula n(n + 1) / 2 confirms for n = 1,000.

Each thread gets its own result variable. The first thread writes `firstHalf`, and the second writes `secondHalf`, and neither reads the other's. Two threads that write different variables don't race, so no mutex is needed.

`join` on both threads is what makes the reads safe. Before the join, `main` can't know that either thread has finished writing its result. After both joins, both results are complete, and adding them is safe.

For the first extension, three threads can take 1 through 333, 334 through 666, and 667 through 1,000. The last value in each range is excluded, so the boundaries must line up exactly: each range starts where the previous one stopped, or numbers get counted twice or skipped.

For the second extension, if both threads add to the same `total`, each `+=` is a read-modify-write, and the two threads can interleave. Some updates are lost. A mutex around each update would make the result correct, at the cost of the threads waiting for each other. Splitting the data so that each thread has its own result avoids that cost entirely, which is why the exercise asks for it.
