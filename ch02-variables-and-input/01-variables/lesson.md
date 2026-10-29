## Variables

A program that only prints fixed text isn't doing much. To work with data, a program needs somewhere to keep it, and a variable is that place. A variable is a named spot in memory that holds a value, and the name lets you refer to the value later.

Here's the first part of this step's program:

```cpp
int number = 10;
std::cout << number << "\n";

number = 15;
std::cout << number << "\n";
```

Press **Run**. The output is:

```
10
15
```

The first line creates the variable. `int` is its type, which tells the compiler what kind of value it can hold, here a whole number. `number` is the name we chose. The `= 10` gives it a starting value. That whole line is called a *declaration*, because it declares that the variable exists.

The second assignment, `number = 15;`, has no type in front of it, because the variable already has one. An assignment replaces the value, and the type stays the same. That's why the second line of output shows 15.

### The types you'll use most

C++ is strict about types, and each one describes a different kind of data:

* `int` holds whole numbers, such as 10 or -3.
* `double` holds numbers with a decimal part, such as 5.99. It's the usual choice for decimals.
* `char` holds a single character, written in single quotes, such as `'a'`.
* `bool` holds true or false. When it's printed, it shows as `0` for false and `1` for true.
* `std::string` holds text, written in double quotes. It comes from the `<string>` header, which is why the program includes it.

The program uses each of these. Run it, and look at the output line for each one.

### More numeric types and characters

The program ends with a few more types, and they behave differently from the ones above.

`float` and `double` both hold numbers with a decimal part. The difference is precision: a `float` keeps about six or seven significant digits, and a `double` keeps about fifteen. That's why the program prints `5.75` for a `float` and `19.99` for a `double`, and why most code uses `double` unless memory is tight. Pick `double` for calculations, and only reach for `float` when you have a reason.

A number can also be written in scientific notation, with an `e` standing for "times ten to the power of". The output line `35000 120000` comes from `35e3` and `12E4`. The `f` at the end of `35e3f` tells the compiler the literal is a `float`, rather than a `double`.

A `char` is a small whole number underneath. The letter `'a'` is stored as the number 97, using the ASCII code. So `char code = 97;` gives the same value as `char code = 'a';`, and printing it shows the letter. You'll rarely write codes like this, but it explains why characters and numbers can be mixed in arithmetic, and why `'a' + 1` gives 98.

### Naming variables

You can call a variable almost anything, but the compiler has rules:

* The name can contain letters, digits, and underscores.
* It can't start with a digit.
* It can't contain spaces or symbols such as `!` or `#`.
* It can't be a keyword that C++ already uses, such as `int`.
* Names are case sensitive, so `number` and `Number` are two different variables.

Within those rules, pick names that say what the value means. `count` or `total_price` tells the next reader far more than `x`.

### Several variables at once

You can declare more than one variable on a line, separated by commas. The program does this with `int x = 5, y = 6, z = 50;`, and it also declares three variables first, second, and third, and gives them all the same value in one line:

```cpp
first = second = third = 50;
```

C++ reads that from right to left, so `third` gets 50 first, then `second` gets the value of `third`, and so on. You'll see this pattern in code from other people, so it's worth recognizing, even if you don't write it yourself.

### Constants

Some values shouldn't change. Adding `const` in front of the declaration makes the variable a constant, and the compiler refuses any attempt to change it:

```cpp
const double pi = 3.14159;
```

Constants make a program easier to read, because `pi` says what the number means, and a reader doesn't have to guess. They also protect you from changing a value by accident in one place when it was meant to stay the same everywhere.

---

### Quiz

*These questions are written for this course.*

````quiz
Which line correctly declares an integer called count, starting at 0?
○ integer count = 0;
→ Not quite. C++ doesn't have an integer type. Its whole-number type is int.
◉ int count = 0;
→ Yes. The type comes first, then the name, then the starting value.
○ count int = 0;
→ Not quite. The type has to come before the name.
○ let count = 0;
→ Not quite. let is a keyword from other languages. C++ needs the type written out.
````

---

### Try it in the runner

Change `pi` to a new value, such as `3.0`, and press **Run**. The program still works, and prints the new value.

Now add `const` to `number` in the first line, and press **Run** again. The build fails, because `number = 15;` tries to change a constant. That's the protection `const` is for, and the compiler catches it before the program ever runs.

---

Variables are the simplest idea in programming, and most of the rest of the course is built on them. Next, we'll look at arithmetic, the calculations you can do with the values you store.
