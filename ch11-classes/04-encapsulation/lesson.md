## Access control and encapsulation

Access control decides which parts of the program can use a class's members. Encapsulation is the design that follows from it: an object keeps its data private, and changes the data only through functions that check each change. The result is that an object can't be left in a state the class doesn't allow.

Here's the class for this step, in `src/main.cpp`:

```cpp
class Car {
public:
    // constructor, getters, setters, and name() go here
private:
    std::string brand;
    std::string model;
    int year = 0;
};
```

The `private:` label means `brand`, `model`, and `year` can't be used from outside the class. `main` can't write `myCar.year` at all. The `public:` section above it is the class's interface, the part the rest of the program can use.

### Getters and setters

Because the data is private, the public functions provide access to it. A getter reads a member, and a setter changes one:

```cpp
int getYear() const { return year; }

void setYear(int yr) {
    if (yr < 1886) {
        throw std::invalid_argument("year is before cars existed");
    }
    year = yr;
}
```

The setter is where encapsulation earns its place. It checks the value before storing it. A year before 1886 is refused, since no car existed before then, and the exception stops the assignment. The object keeps its last valid year.

Press **Run**. The output is:

```
1969 Ford Mustang
2014 Ford Mustang
year is before cars existed
2014 Ford Mustang
```

The setter accepts 2014. The attempt to set 1700 throws, the catch prints the message, and the last line shows that the year is still 2014. The bad value never reached the object.

### The constructor uses the setter

The constructor calls `setYear(yr)` rather than assigning `year` directly. That way, the same check applies to an object's first value as to every later change. A constructor that bypassed the setter could create a car with a year the setter would refuse, which would make the rule easy to break.

### Why keep data private

Private data can be changed in one place, the class itself, so a rule written there applies everywhere. If the program stored the year in a public member, every part of the program would have to remember the rule, and one forgotten check would let a bad value in. The private member and the setter keep the rule in a single place.

---

### Quiz

*These questions are written for this course.*

````quiz
Why does the setter check the year before storing it?
○ Because the compiler requires a check in every setter.
→ Not quite. The compiler doesn't require it. The class does, to keep its rule.
◉ So an object can't be left with a year that the class's rules don't allow.
→ Yes. The check keeps every change inside the rules the class sets.
○ Because the year is stored as text.
→ Not quite. The year is an int, and the check is about its value.
````

````quiz
Which statement about `private` members is true?
○ Any part of the program can read them.
→ Not quite. Private members are hidden from outside the class.
◉ They can be used only from inside the class's own functions.
→ Yes. Outside code must go through the public functions.
○ They can't be used by any function, even inside the class.
→ Not quite. Member functions of the class can use them freely.
````

---

### Try it in the runner

Add the line `myCar.year = 1700;` to `main`, and predict whether it compiles. It doesn't: `year` is private, so `main` can't reach it. Use `setYear` instead, as the program does, and the check runs.

Then add `getYear()` to the program's output, and predict the value it returns after the failed call to `setYear(1700)`. It's 2014, since the setter refused the change.

---

Encapsulation keeps an object's rules in one place, and the setters enforce them. The summary and homework ask you to build a class of your own, using both ideas.
