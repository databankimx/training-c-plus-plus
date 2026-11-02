## Command-line arguments

So far the program asks the user for values once it's running. Many programs take their values before they start, by reading words typed after the program's name. Those words are called command-line arguments. You've already used them: the runner's argument box sends whatever you type there to the program in exactly this way.

Here's the program for this step. Press **Run** with no arguments first, then type the arguments in the box, as `4 9`, and press Run again.

```cpp
int main(int argc, char* argv[]) {
    std::cout << "Arguments received: " << argc - 1 << "\n";
    for (int i = 1; i < argc; i++) {
        std::cout << "Argument " << i << ": " << argv[i] << "\n";
    }

    if (argc == 3) {
        const int first = std::stoi(argv[1]);
        const int second = std::stoi(argv[2]);
        std::cout << first << " + " << second << " = " << first + second << "\n";
    } else {
        std::cout << "Give two numbers, for example: program 4 9\n";
    }
    return 0;
}
```

Run it with the arguments `4 9`. The output is:

```
Arguments received: 2
Argument 1: 4
Argument 2: 9
4 + 9 = 13
```

With no arguments, the output is the single line asking for two numbers, and `Arguments received: 0`.

### argc and argv

`main` takes two parameters that carry the arguments. `argc` is the number of words on the command line, and `argv` is an array holding the words as text. The words are counted from the program's own name, so `argv[0]` is the program's name, and the first argument the user typed is `argv[1]`.

That's why the loop starts at 1, not 0. Starting at 0 would print the program's own name as well, and the path to the program varies from one computer to another, so it's left out of the output.

### Arguments are text

Every argument arrives as a `char*`, which is text, even when it looks like a number. `std::stoi` converts the text to an `int`, the same kind of conversion the user-input step used with `cin`. The conversion is done when you ask for it, so a program that expects numbers must convert them itself.

### Arguments and the runner

The runner's argument box splits what you type at each space, and sends each word as a separate argument. That's why `4 9` gives two arguments, and why a program that needs the whole line of text has to join the words back together.

---

### Quiz

*These questions are written for this course.*

````quiz
For the command `program 4 9`, what is `argc`?
○ 2
→ Not quite. argc also counts the program's own name.
◉ 3
→ Yes. The program's name, 4, and 9 make three words.
○ 4
→ Not quite. Only the program's name and the two numbers are counted.
````

````quiz
Why does the loop in this step start at 1, not 0?
○ Because argv[0] is an empty string.
→ Not quite. argv[0] holds the program's name, which isn't empty.
◉ Because argv[0] is the program's own name, and the first argument the user typed is argv[1].
→ Yes. Starting at 1 skips the program's name.
○ Because argc is always 0.
→ Not quite. argc counts the words, and is 0 only when nothing was typed.
````

---

### Try it in the runner

Run the program with the arguments `4 nine`. The second argument isn't a number, so `std::stoi` can't convert it, and the program stops with an error message, which is a crash rather than a clear error. Predict the message before you press Run. Handling bad input like this properly is the job of exceptions, which a later chapter covers.

Then run with no arguments at all, and predict the second line of the output.

---

Command-line arguments let a program take its values before it starts, which suits programs that run unattended, or that are used from a script. The summary comes next, and it covers the whole chapter.
