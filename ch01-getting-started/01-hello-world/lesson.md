## Hello, world

Every programming course starts with a program that prints a message. It's the smoke test of the whole setup: if this runs, your compiler, your build tools, and the runner are all on speaking terms. This one prints two lines, so you can also see how a C++ program is put together.

Here's the program, in `src/main.cpp`:

```cpp
#include <iostream>

int main() {
    std::cout << "Hello World!\n";
    std::cout << "I am learning C++";

    return 0;
}
```

Press **Run**, or press F5. The Output pane should look something like this:

```
Configuring 01-hello-world...
Building 01-hello-world...
Running program.exe

Hello World!
I am learning C++
— Finished with exit code 0 —
```

The first line is the important one to understand. C++ is a compiled language, which means the text in `main.cpp` isn't the program. It's a set of instructions that a compiler turns into one. Running the program happens in three stages, and the runner shows you each one:

* **Configuring** is CMake reading the step's `CMakeLists.txt`, and working out how to build it. This only changes when the build setup changes, so it's quick.
* **Building** is the compiler turning `main.cpp` into a program. The first build can take several seconds, and later ones are much faster, because only the changed files are compiled again.
* **Running** starts the program that the build produced.

The blank line before the program's output is there on purpose. It separates the build from what your program prints, so the two don't run together.

At the end, the runner shows the exit code. Zero means the program finished without a problem.

### What the program is made of

Each part of the program has a job, and you'll meet every one of them again.

* `#include <iostream>` brings in the input and output library. Without it, `std::cout` doesn't exist. The angle brackets tell the compiler to look in the standard library.
* `int main()` is where the program starts. Every C++ program has exactly one `main`, and the operating system always calls it first.
* `std::cout << "..."` writes text to the output. The `<<` operator sends each piece to `cout`, which stands for character output. You can chain as many pieces as you like.
* `\n` is a newline. Without it, the second line would follow the first on the same line, which is why the first line has one and the second doesn't.
* `return 0;` tells the operating system the program finished successfully. A non-zero value means something went wrong, and that matters when scripts run your program.

The `std::` in front of `cout` looks like clutter at first, but the next step explains why it's there.

---

### Quiz

*These questions are written for this course.*

````quiz
Which header brings in `std::cout`?
○ <stdio.h>
→ Not quite. <stdio.h> is the C library. std::cout comes from the C++ library.
◉ <iostream>
→ Yes. <iostream> provides std::cout, along with other input and output objects.
````

---

### Try it in the runner

Replace `\n` in the first line with `std::endl`, and press **Run** again. The output looks the same, and it's worth knowing why. `std::endl` writes a newline and also flushes the output, which means it pushes the text out right away. `\n` only writes the newline. For a program like this, either one is fine.

---

And that's your first C++ program, built and run by the same tools that the professionals use. Nothing about it was magic, and every line had a reason to be there.
