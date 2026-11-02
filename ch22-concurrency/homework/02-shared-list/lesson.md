## Homework: Shared list

Two threads add values to one shared `std::vector`. The vector is protected by a mutex, so the two threads never change it at the same moment. The order in which the values arrive depends on the threads, so the program prints only results that don't depend on that order.

The program should:

* write `addValues(std::vector<int>& list, std::mutex& lock, int first, int last)`, which adds each number from `first` up to, but not including, `last` to the list. Each `push_back` happens while holding the lock, through a `std::lock_guard`
* in `main`, create an empty vector and a mutex, start one thread that adds 1 through 5, and a second that adds 6 through 10
* join both threads, then print `Size: ` followed by the vector's size, and `Sum: ` followed by the sum of its values

### What to check

The output should be:

```
Size: 10
Sum: 55
```

The order of the values in the vector can differ from one run to the next, and the program doesn't print them. The size and the sum are the same every time, which is what the mutex guarantees.

### Extensions

* Print the vector in sorted order, using the sort from Chapter 16 after both threads have finished. Explain why the sort is safe to run without the lock at that point.
* Remove the lock, and explain why the size might come out wrong. Then explain why the program could still appear to work most of the time.

---

*This exercise is not from the book. It practices the ideas in Chapter 22, with the containers from Chapter 14.*
