## Threads

So far every program has run one thread of work, one step after another. A thread is an independent sequence of work that runs alongside the others. Modern computers have several processors, and threads let a program use them at the same time, or let one part of a program wait while another keeps going.

The standard library's thread support is in `<thread>`. Here's the core of the program from `src/main.cpp`:

```cpp
void greet(std::string name) {
    std::cout << "Hello from " << name << "\n";
}

std::thread worker(greet, "worker");
worker.join();
```

The `std::thread` object starts a new thread that runs `greet` with the argument "worker". The thread starts running as soon as the object is created. `join` waits for the thread to finish, and it must be called before the thread object goes out of scope. A `std::thread` that is destroyed while still running, without being joined or detached, makes the program stop.

Press **Run**. The output is:

```
Start
Hello from worker
After join
```

The `join` call is what puts the output in this order. The thread prints its message while `main` waits, and `After join` prints only once the thread has finished.

### Why join matters

Without `join`, `main` would carry on while the thread runs, and the two could print in either order. A thread can outlive the code that started it, and it can still be using data from the function that created it, which is a common source of bugs. `join` makes the rule explicit: the work is finished before the code that depends on it continues.

The thread object owns a running thread, and the RAII rule from the smart pointers chapter applies to it. If a thread object goes out of scope while still joinable, the program stops. Joining it before the end of its scope keeps that from happening.

### Output from several threads

When two threads print at once, their output can interleave in any order. A message can be split between threads in the middle of a line. The course won't show that here, because the output would differ from run to run. The next step shows how to share data between threads safely, and the homework shows how to split work so that no sharing is needed.

---

### Quiz

*These questions are written for this course.*

````quiz
What does `join` do?
○ It starts a new thread.
→ Not quite. Creating the std::thread object starts the thread.
◉ It waits until the thread has finished before the calling code continues.
→ Yes. Without join, the two threads can run in either order.
○ It stops the thread.
→ Not quite. join waits for the thread to finish, and doesn't stop it.
````

````quiz
What happens if a `std::thread` is destroyed while it is still running and has not been joined or detached?
○ It keeps running in the background without any problem.
→ Not quite. The program stops in that case, so the thread must be joined or detached first.
◉ The program stops, because the thread object was destroyed while its thread was still joinable.
→ Yes. Every started thread must be joined or detached before its object goes out of scope.
○ The thread finishes early and its output is lost.
→ Not quite. The program ends instead, and the thread is not allowed to run on its own.
````

---

### Try it in the runner

Add a second thread that calls `greet` with a different name, and join it after the first. Predict whether the two greetings always appear in the same order before you press **Run**. They might not. Without a join between the two starts, the threads run at the same time, so the order can change from one run to the next.

---

A thread runs a function at the same time as the code that started it, and `join` is how the program waits for it. The next step is the harder part: two threads that change the same data, and the mutex that keeps those changes from colliding.
