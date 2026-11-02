## Mutexes

Two threads that change the same variable at the same time can get the wrong result. An increment, `total++`, is really three steps: read the value, add one, and write it back. If two threads read the same value before either writes, one of the increments is lost. That's a data race, and in C++ a data race is undefined behavior, which means the program's result isn't guaranteed at all.

A mutex, short for mutual exclusion, is a lock that only one thread can hold at a time. A thread that wants to change shared data takes the lock first, changes the data, and releases the lock. Any other thread that wants the lock waits until it's free.

The program in this step uses a `std::lock_guard`, which takes the lock when it's created and releases it when it goes out of scope. That's the RAII pattern from the smart pointers chapter, applied to a lock:

```cpp
void addMany(int& total, std::mutex& lock, int times) {
    for (int i = 0; i < times; i++) {
        std::lock_guard<std::mutex> guard(lock);
        total++;
    }
}
```

Each pass of the loop locks the mutex, adds one, and unlocks it at the closing brace of the loop body. The lock is released on every path out of the body, so it can't be left held by mistake.

### Passing references to threads

The threads receive `total` and `lock` by reference, so both threads change the same variable and use the same mutex. The arguments to `std::thread` are copied by default, which would give each thread its own `total`. `std::ref` wraps a variable so that the thread receives a reference to it instead.

Press **Run**. The output is:

```
Total: 200000
```

Each thread adds 100,000, and the total is 200,000 only because no increment was lost. The lock forces the threads to take turns on the shared counter.

### The cost of the lock

A lock makes the threads wait for each other. In this program, almost all the time goes into taking and releasing the lock, so the threads gain little from running at the same time. Real programs lock as little as they can, for as short a time as possible, and try to avoid sharing data at all. The homework shows one way to do that.

### Deadlock

Two threads that each hold a lock and wait for the other's lock will wait forever. That's a deadlock. The usual cause is taking locks in different orders in different places. A program that takes its locks in one fixed order avoids it, and the standard library offers `std::scoped_lock` for taking several locks safely at once.

---

### Quiz

*These questions are written for this course.*

````quiz
Why can two threads that increment a shared counter without a lock get the wrong total?
○ Because the compiler refuses to build the program.
→ Not quite. The program builds, and the problem appears at run time.
◉ Because each increment reads, adds, and writes, and two threads can interleave those steps so that an update is lost.
→ Yes. That's a data race, and the result isn't guaranteed.
○ Because increments are always lost when threads run together.
→ Not quite. Lost updates can happen, but the result isn't always wrong, and the outcome isn't guaranteed either way.
````

````quiz
What does `std::lock_guard` do when it's created and destroyed?
○ It locks the mutex when created and never unlocks it.
→ Not quite. It also releases the lock when it goes out of scope.
◉ It locks the mutex when created, and unlocks it when it goes out of scope.
→ Yes. That's the RAII pattern applied to a lock.
○ It copies the mutex, so each thread has its own lock.
→ Not quite. The guard refers to the same mutex, so all threads share it.
````

---

### Try it in the runner

Remove the `lock_guard` line from `addMany`, and run the program several times. The total might come out below 200000, and it might not. Predict what you'd see, and explain why a result that's correct sometimes is still a bug. A program that's correct only some of the time is not correct.

---

A mutex lets one thread at a time change shared data, and a `lock_guard` makes sure the lock is always released. The chapter's last steps cover the summary and two homework exercises that split work so that little or nothing is shared.
