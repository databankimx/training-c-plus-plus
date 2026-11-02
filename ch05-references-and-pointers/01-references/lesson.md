## References

A variable is a name for a value stored in memory. Sometimes you want a second name for the same value, so that either name refers to one thing. A reference does that. It's declared with an `&` after the type, and it becomes another name for an existing variable.

Here's the program for this step, in `src/main.cpp`:

```cpp
std::string food = "Pizza";
std::string& meal = food;   // meal is another name for food

std::cout << food << "\n";
std::cout << meal << "\n";
```

Press **Run**. The output is:

```
Pizza
Pizza
```

Both lines print the same string, because `meal` isn't a copy of `food`. It's a second name for the same variable. The `&` in `std::string& meal` is part of the declaration, and it means "reference". It isn't the address-of operator, which you'll meet in the pointers step, and that's an easy point to mix up.

Next, the program changes the value through the reference:

```cpp
meal = "Tacos";
std::cout << food << "\n";
```

The output is `Tacos`. Assigning to `meal` assigned to `food`, since they are the same variable under two names. You don't need any special syntax to use a reference, and it behaves like the variable it refers to.

### Rules for references

A reference has to be set up when it's declared, and it can't be left empty:

```cpp
std::string& nothing;   // error: a reference must refer to something
```

Once set, a reference always refers to the same variable. Assigning to it changes the variable, and never makes the reference point somewhere else. That's the main difference from the pointers you'll see in the next step.

A reference also has to refer to a variable that exists. You can't make a reference to a number such as 42, since there's no variable to name. A `const` reference can refer to a value that isn't a variable, but that's a topic for a later chapter.

### Why references matter

You already saw references as parameters, where the `&` lets a function change its caller's variable. A reference declared inside a function works the same way, to give a long name a short alias, or to refer to one element of a larger structure without copying it. The rules are the same whatever the reason: the reference and the variable are one thing.

---

### Quiz

*These questions are written for this course.*

````quiz
After `int& r = n;`, what happens when you write `r = 5;`?
○ r becomes a separate variable holding 5, and n is unchanged.
→ Not quite. A reference doesn't create a new variable. It's another name for n.
◉ n becomes 5, because r is another name for n.
→ Yes. Assigning through a reference changes the variable it refers to.
○ An error, because a reference can't be assigned to.
→ Not quite. A reference can be assigned to. It's the variable that changes.
````

````quiz
Which declaration is invalid?
○ int& r = n;
→ Not quite. This is a valid reference to an existing int.
◉ int& r;
→ Yes. A reference must be set up when it's declared, so this won't compile.
○ int& r = other;
→ Not quite. This refers to another existing int, which is valid.
````

---

### Try it in the runner

Add a second reference to `food`, called `dinner`, and change `dinner` to `"Soup"`. Predict what `food` and `meal` show before you press **Run**. They all show `Soup`, since all three names refer to the same variable.

---

A reference is another name for an existing variable, and it has to be set up when it's declared. The next step, pointers, is also a way to refer to a variable, but a pointer holds a separate value that says where the variable is, and it can point somewhere else.
