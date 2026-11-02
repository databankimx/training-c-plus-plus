## Initializing structures

A new variable with no initial values can hold anything, and that's a risk for a structure as much as for a plain variable. Two tools help. A member can have a default value, which applies whenever a variable doesn't set it. And a variable can be initialized with braces, which lists the values in the order the members are declared.

Here's the structure for this step, in `src/main.cpp`:

```cpp
struct Settings {
    std::string name = "default";
    int volume = 5;
    bool muted = false;
};
```

Each member has an `=` and a value. Those values are the defaults, and they're used for any variable that doesn't provide its own.

Press **Run**, and look at the output:

```
default 5 no
Scott 9 yes
Scott 1 yes
```

### Default values

`Settings a;` declares a variable and sets nothing. Its members take the defaults, so `a` has the name `default`, volume 5, and `muted` set to false. The output's first line shows that.

### Brace initialization

`Settings b{"Scott", 9, true};` gives the values in order: the first goes to `name`, the second to `volume`, and the third to `muted`. The order must match the declaration. Swapping the volume and the name would fail to compile, since a number can't become a string. Brace initialization is the usual way to set several members at once, and the compiler checks each value against its member's type.

### Copies are independent

`Settings c = b;` creates a new variable that starts as a copy of `b`. The next line changes only `c`:

```cpp
c.volume = 1;
```

The third line of output shows the change, and the second line still shows `b` with volume 9. A copy is a separate structure, and changing one never changes the other.

---

### Quiz

*These questions are written for this course.*

````quiz
What are the members of `Settings a;` with no initializer?
○ They are all zero or empty, whatever the defaults say.
→ Not quite. Members with a default value take that default.
◉ Each member takes its default value, such as volume 5.
→ Yes. A member with a default value is set to it when the variable is created.
○ The program won't compile, because the members have no values.
→ Not quite. Declaring a variable with defaults is valid.
````

````quiz
In `Settings b{"Scott", 9, true};`, which member receives 9?
○ name
→ Not quite. name receives the first value, "Scott".
◉ volume
→ Yes. The values are matched to the members in the order they are declared.
○ muted
→ Not quite. muted receives the third value, true.
````

---

### Try it in the runner

Add `Settings d{"Ada"};` and `show(d);` to the program, and predict the output before you press **Run**. The name is `Ada`, and the volume and muted values are not given, so they take their defaults: volume 5, and muted no. The line should read `Ada 5 no`.

Then try `Settings e{5, "Ada"};`, with the values in the wrong order, and press **Run**. The build fails, because 5 can't become a string.

---

Default values and brace initialization make a structure's starting state clear and safe. The homework applies structures to a small task, and the summary brings the chapter together.
