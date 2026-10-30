## User input

So far, every value in our programs was decided before the program ran. That's fine for learning, but most real programs need to ask something of the person using them. C++ handles that through the same stream idea you met with `std::cout`, only in the other direction. `std::cin` is the stream for input, and it reads what the user types.

Here's the program for this step. Press **Run**, and type into the input box at the bottom of the Output pane when it asks you to. Press Enter after each answer.

```
Enter some text: I like C++
You entered: I like C++
Enter a number: 4
You entered: 4
Enter another number: 9
You entered: 9
4 + 9 = 13
```

Your answers will be different, of course. The shape of the output is what matters.

### Reading a whole line

For the first question, the program uses `std::getline`:

```cpp
std::string text;
std::getline(std::cin, text);
```

`getline` reads everything the user types up to the Enter key, including spaces. That's what you want for a name, a sentence, or anything else where the spaces matter.

### Reading a number

For the numbers, the program uses `std::cin >>`:

```cpp
int x = 0;
std::cin >> x;
```

The `>>` operator reads the next value from the input, and converts it into the type of the variable. Because `x` is an `int`, `cin` looks for a whole number. It skips any spaces before the number, and it stops at the first character that isn't part of it.

That's useful, but it has a catch. `cin >>` doesn't read the Enter key, so the newline stays in the input. If you mix `cin >>` with `getline` in the wrong order, `getline` can read that leftover newline and return an empty line. The program avoids the problem by reading the text first, and then using `cin >>` for the numbers.

### Why the prompts use flush

Look at the first line of the program:

```cpp
std::cout << "Enter some text: " << std::flush;
```

The prompt has no newline at the end, so the output could wait in a buffer before it appears. `std::flush` pushes the text out at once, so the user sees the question before they're asked to answer it. Without it, a program can sit silently with no prompt on the screen, which is confusing.

---

### Quiz

*These questions are written for this course.*

````quiz
Which function reads a whole line of text from the user, including spaces?
○ std::cin >> text
→ Not quite. cin >> stops at the first space, so it would only read one word.
○ std::cout << text
→ Not quite. cout writes to the output. It doesn't read anything.
◉ std::getline(std::cin, text)
→ Yes. getline reads up to the Enter key, spaces included.
````

---

### Try it in the runner

At the second prompt, type a word such as `hello` instead of a number. Press **Run** again, and type `hello` at the second prompt.

The program can't turn `hello` into a number, so `cin` fails, and the program prints `0` for `x`, which is the value it started with. The later lines still run, because the program doesn't check for the failure. A real program should check, and later chapters show how.

---

Being able to ask the user for something is the first step toward programs that respond to their input. The summary and the homework come next, and they'll put the whole chapter to work.
