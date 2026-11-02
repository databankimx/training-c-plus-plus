## Namespaces

In the last lesson, every name from the standard library had `std::` in front of it. That prefix is a namespace, and it's worth understanding before we go further, because you'll be typing it constantly.

A namespace is a named container for names. The standard library puts everything in `std`, so its `cout` is really `std::cout`. The reason for the container is simple: if you write your own `cout`, or a library you use brings one in, the two can't clash, because they live in different namespaces.

Here's the same program written the other way, which you'll see in a lot of tutorials and examples:

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Hello World!" << endl;
    return 0;
}
```

Press **Run**. The output is the same:

```
Hello World!
```

The `using namespace std;` line says, in effect, "I'm happy for every name in `std` to be used without its prefix." That lets you write `cout` and `endl` instead of `std::cout` and `std::endl`. It's shorter, and it's easy to read on a small screen.

It also has a cost, which is why most professional code avoids it. Once `std` is open, every name in it is visible, and a name you define yourself might clash with one from the library. The standard library is big, so the clash may not happen today, but it can happen after a library update, and the error message won't help you much.

My advice is to write `std::` in full while you're learning, so you always know where a name comes from. Put `using namespace std;` in a source file only if you're sure about what you're doing. Never put it in a header file, where it spreads into every file that includes it.

`endl` is the same kind of name as `cout`. It writes a newline, and it flushes the output. You met `\n` in the last lesson, which writes a newline without the flush.

---

### Quiz

*These questions are written for this course.*

````quiz
Which statement best describes what `using namespace std;` does?
○ It copies the standard library into your program.
→ Not quite. The library is linked in either way. The line only changes how names are looked up.
◉ It makes the names in std usable without the std:: prefix.
→ Yes. The compiler then looks for cout and endl in std, so you can write them without the prefix.
○ It has to appear in every C++ program, or the program won't compile.
→ Not quite. Many programs leave it out and write std:: in full, and they compile just as well.
○ It makes the program's output faster.
→ Not quite. It only changes how names are found, and it has no effect on how the program runs.
````

---

### Try it in the runner

Remove the `using namespace std;` line, and press **Run**. The build fails, and the Output pane shows an error saying `cout` and `endl` aren't declared. That's the compiler telling you it doesn't know what those names mean in this file.

Put the line back, or add `std::` in front of each name, and the program builds again. Either fix is correct.

---

Namespaces take a little getting used to, but they're one of the first things that make large C++ programs manageable. Once you see how they stop names from colliding, the `std::` prefix starts to look like a good habit rather than clutter.
