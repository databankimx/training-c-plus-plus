## Strings

Numbers aren't the only thing programs work with. Names, messages, file paths, and the text a user types are all strings. In C++, a string is a `std::string`, and it comes from the `<string>` header. You've already used one: the name in the input step was a `std::string`.

This is an introduction, so we'll keep it to the basics you'll need in the next step and the homework. We come back to strings in much more depth later in the course, where we look at searching, splitting, and the rules for working with text safely.

Here's the program for this step, in `src/main.cpp`:

```cpp
std::string first = "Hello";
std::string second = "C++";
std::string greeting = first + ", " + second + "!";
std::cout << greeting << "\n";
```

Press **Run**. The output is:

```
Hello, C++!
```

Three things happen here. Each string is created with its text in double quotes. The `+` operator joins strings together, so `greeting` is built from the pieces. And `greeting` is printed like any other value.

### Quotes matter

Double quotes make a string, as in `"Hello"`. Single quotes make a single character, as in `'H'`. The two are different types, so `"H"` and `'H'` aren't interchangeable. The compiler will reject one where the other is expected.

### Length and positions

The next lines of the program ask about the string itself:

```cpp
std::cout << "Length: " << greeting.size() << "\n";
std::cout << "First letter: " << greeting[0] << "\n";
```

The output is:

```
Length: 11
First letter: H
```

`greeting.size()` returns the number of characters, including spaces and punctuation. Notice that the function name is followed by empty parentheses. That's a call to a function that belongs to the string, and you'll see that pattern a lot.

`greeting[0]` gives the character at position 0. Positions in C++ start at zero, not one, so the first character is at 0, the second at 1, and so on. This is the most common source of off-by-one mistakes, and you'll meet it again.

### Adding to a string

`+=` adds text to the end of a string, the same way `+=` adds to a number:

```cpp
greeting += " Welcome.";
```

Now `greeting` holds `Hello, C++! Welcome.`. Like the number operators, `+=` changes the variable itself.

### Special characters

A string can't contain a double quote directly, because the quote would end the string. Instead you write a backslash in front of it, which is an escape sequence:

```cpp
std::cout << "Tab:\tBackslash:\\ Quote:\"\n";
```

`\t` is a tab, `\\` is a single backslash, and `\"` is a double quote. The output shows the tab as a gap, and the other two as the characters themselves.

---

### Quiz

*These questions are written for this course.*

````quiz
What is the position of the first character in a `std::string`?
○ 1
→ Not quite. C++ starts counting positions at zero.
◉ 0
→ Yes. The first character is at position 0, and the second is at position 1.
○ -1
→ Not quite. Positions run from zero upwards.
````

````quiz
Which expression gives the number of characters in `name`?
○ name.length
→ Not quite. length is a function, so it needs its parentheses.
◉ name.size()
→ Yes. size() returns the number of characters, spaces and punctuation included.
○ name[size]
→ Not quite. That's not a valid way to ask for the size.
````

---

### Try it in the runner

Change `greeting[0]` to `greeting[4]`, and predict the letter before you press **Run**. Position 4 is the fifth character, which is `o` in `Hello`. Then try a position past the end, such as `greeting[50]`. The program may print something unexpected, or crash. That's a sign you've read outside the string, and a later chapter shows how to guard against it.

---

That's enough about strings for now. The next step asks the user for text, which is where you'll first put a string to work with real input.
