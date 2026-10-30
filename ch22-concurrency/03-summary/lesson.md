## Summary: Concurrency

This chapter covered running work on several threads, and keeping shared data safe when they touch it.

* **A thread runs alongside the code that started it.** `std::thread` starts it, and the function's arguments are copied unless they're wrapped with `std::ref`.
* **`join` waits for a thread to finish.** A thread must be joined or detached before its object goes out of scope, or the program stops.
* **Output from threads can interleave.** Without `join`, or with unsynchronized printing, the order changes from run to run.
* **A data race is undefined behavior.** Two threads that change the same data without coordination can lose updates.
* **A mutex lets one thread at a time through.** A thread locks it before using shared data, and unlocks it when done.
* **`std::lock_guard` ties the lock to a scope.** It locks on creation and unlocks at the closing brace, on every path out.
* **Less sharing means fewer locks.** Splitting work so each thread writes its own result avoids most of the problem.
* **Deadlock comes from inconsistent lock order.** Taking locks in one fixed order avoids it.

### Check your understanding

*These questions are written for this course.*

````quiz
What does `join` guarantee about a thread?
○ That the thread has started.
→ Not quite. Creating the std::thread object already starts the thread.
◉ That the thread has finished before the calling code continues past join.
→ Yes. join is the point where the program waits for the thread's work.
○ That the thread's output appears before the program's output.
→ Not quite. join orders the finish of the work, not the order of unrelated output.
````

````quiz
Why is a data race a serious bug, even when the result is sometimes correct?
○ Because it makes the program slower.
→ Not quite. The problem is correctness, not speed.
◉ Because the result isn't guaranteed, so a program that works in testing can fail later.
→ Yes. A result that is correct only some of the time is not a correct program.
○ Because the compiler refuses to build such a program.
→ Not quite. The program builds, and the problem appears at run time.
````

````quiz
Two threads each take lock A, then lock B. A third thread takes lock B, then lock A. What is the risk?
○ The program runs more slowly.
→ Not quite. The risk is that it stops making progress at all.
◉ A deadlock, in which the threads wait for each other's locks forever.
→ Yes. Taking locks in inconsistent orders is the usual cause.
○ The locks are shared, so each one counts twice.
→ Not quite. Lock counts don't change in that way.
````
