## Function templates

Some functions do the same thing for many types. A function that returns the larger of two values works the same way for integers, decimals, and strings. Writing one version per type would repeat the code, and a bug fixed in one copy would be missing from the others. A template writes the function once, with a placeholder for the type, and the compiler produces a real version for each type the program uses.

Here's the template from `src/main.cpp`:

```cpp
template <typename T>
T largerOf(T a, T b) {
    return a > b ? a : b;
}
```

The line `template <typename T>` introduces a type parameter named `T`. Inside the function, `T` stands for whatever type is used. The `>` comparison and the conditional operator from the decisions chapter both work for any type that supports them.

### Deduction

The compiler usually works out `T` from the arguments:

```cpp
std::cout << largerOf(3, 7) << "\n";
std::cout << largerOf(2.5, 1.5) << "\n";
```

The first call passes `int` values, so `T` is `int`. The second passes `double` values, so `T` is `double`. The compiler generates each version when it needs it, and the output is:

```
7
2.5
```

### Naming the type

Sometimes the arguments don't settle the type, or you want to be explicit. The type goes in angle brackets after the name:

```cpp
std::cout << largerOf<std::string>("apple", "banana") << "\n";
```

Here `T` is `std::string`, and the two string literals convert to it. The output is `banana`, since it comes later in the alphabet.

### What a template needs

A template is a pattern, not a function. The compiler can only generate a version when it sees both the template and the type it's used with, so the full definition has to be visible at the point of use. That's why templates are usually written in headers, as the headers chapter explained. A template defined only in a source file can't be used from other files.

Each type you use gives the compiler another version to build, and an error in the template shows up only when it's used with a type that exposes the error. The program's code is checked when it's instantiated, not when the template is written.

---

### Quiz

*These questions are written for this course.*

````quiz
What does `template <typename T>` introduce?
○ A function that takes a type as an argument at run time.
→ Not quite. Templates are resolved at compile time, not with a run-time argument.
◉ A type parameter, a placeholder that the compiler fills in for each type the template is used with.
→ Yes. T stands for a real type in each generated version.
○ A class that can hold any value.
→ Not quite. It creates a pattern for a function, or for a class if the template is written for one.
````

````quiz
Why are templates usually defined in header files?
○ Because headers are faster to compile.
→ Not quite. The reason is visibility, not speed.
◉ Because the compiler needs the full template wherever it's used to generate each version.
→ Yes. A template defined only in a source file can't be instantiated from other files.
○ Because templates can't be compiled at all.
→ Not quite. Templates compile, as long as their definition is visible at the point of use.
````

---

### Try it in the runner

Call `largerOf(3, 2.5)` and predict whether the compiler accepts it before you press **Run**. It refuses: the compiler deduces `T` as `int` from the first argument and as `double` from the second, and the two conflict. Fix it by naming the type, as in `largerOf<double>(3, 2.5)`, which converts the `3` to a `double`.

---

A function template writes one function that works for many types, and the compiler generates each version. The next step applies the same idea to classes, where a whole container or wrapper can be written once for any type.
