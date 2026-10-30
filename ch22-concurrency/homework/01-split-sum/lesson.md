## Homework: Split sum

Add the whole numbers from 1 to 1,000 by splitting the work between two threads. Each thread writes only its own result, so the threads share no data, and no lock is needed.

The program should:

* write `sumRange(int first, int last, long long& total)`, which adds the numbers from `first` up to, but not including, `last`, and stores the result in `total`
* in `main`, declare two `long long` variables, one for each half, both starting at 0
* start one thread that sums 1 through 500, and a second that sums 501 through 1,000, passing each result variable with `std::ref`
* join both threads, and print `Sum: ` followed by the two results added together

Link the thread library in the step's CMake file, as the chapter's steps did.

### What to check

The output should be:

```
Sum: 500500
```

The two halves are 125,250 and 375,250. Each thread writes only its own variable, so there's no race, and the join ensures both results are complete before `main` reads them.

### Extensions

* Use three threads instead of two. Decide where the ranges should split, so that every number is counted once.
* Change both threads to write to the same `total`. Explain why the result is no longer safe, and what a mutex would add.

---

*This exercise is not from the book. It practices the ideas in Chapter 22.*
