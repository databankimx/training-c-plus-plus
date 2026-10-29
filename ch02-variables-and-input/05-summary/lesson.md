## Summary: Variables and input

This chapter covered how a program keeps values, and how it gets them from the person using it.

* **A variable is a named place for a value.** You declare it with a type, such as `int`, `double`, `char`, `bool`, or `std::string`, and assign to it afterwards. The type stays the same for the life of the variable.
* **Naming matters.** Names are case sensitive, can't start with a digit, and can't be a keyword. Pick names that say what the value means.
* **`const` protects a value.** A constant can be declared and read, but any attempt to change it is a compile error.
* **`std::getline` reads a whole line.** It includes spaces, and it stops at the Enter key.
* **`std::cin >>` reads one value.** It converts the text into the type of the variable, and it stops at the first space or non-matching character.
* **Mixing the two needs care.** Reading a line first and then numbers avoids the leftover newline problem.
* **Flush prompts.** `std::flush` sends the prompt to the screen before the program waits for an answer.
* **Strings hold text.** `std::string` is created with double quotes, joined with `+`, and grown with `+=`. `size()` gives the length, and positions start at 0.
* **Numeric types differ in precision.** `double` keeps about fifteen significant digits, and `float` about six or seven. `char` holds a small number, its ASCII code, and prints as a letter.
* **Math functions are in `<cmath>` and `<algorithm>`.** `std::sqrt`, `std::pow`, `std::round`, `std::floor`, and `std::ceil` work on decimals, and `std::max` and `std::min` compare two values.
* **Arithmetic uses `+`, `-`, `*`, `/`, and `%`.** `%` gives the remainder.
* **Integer division drops the fraction.** When both sides are `int`, `7 / 2` is 3. Use a decimal, such as `2.0`, or `static_cast<double>`, to keep the fraction.
* **Precedence decides the order.** Parentheses come first, then `*`, `/`, and `%`, then `+` and `-`. Operators at the same level go from left to right. When in doubt, add parentheses.
* **`++` and `+=` change a variable in place.** `count++` adds one, and `count += 5` adds five.
* **`std::setprecision` controls decimal output.** Pair it with `std::fixed` to print a fixed number of places after the point.

### Check your understanding

*These questions are written for this course.*

````quiz
Which type should you use to hold a price such as 5.99?
○ int
→ Not quite. int holds whole numbers, so the decimal part would be lost.
◉ double
→ Yes. double holds numbers with a decimal part.
○ char
→ Not quite. char holds one character, not a number.
````

````quiz
What happens if you try to change a `const` variable after it's declared?
○ The new value replaces the old one, with a warning.
→ Not quite. A const variable can't be changed, and the compiler is strict about it.
◉ The build fails with a compile error.
→ Yes. The compiler refuses the assignment, and the program doesn't run.
○ The program runs, but the old value is kept.
→ Not quite. The program doesn't run at all if the build fails.
````

````quiz
Which line reads a whole line of text, including spaces, into `name`?
○ std::cin >> name;
→ Not quite. cin >> stops at the first space, so it reads only one word.
◉ std::getline(std::cin, name);
→ Yes. getline reads everything up to the Enter key.
○ std::cout << name;
→ Not quite. That line writes the name out. It doesn't read anything in.
````
