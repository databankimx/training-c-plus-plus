## Return values and overloading

A function that only prints is useful, but many functions are better at calculating something and handing the result back. A function that returns a value gives its caller a result to store, print, or use in another calculation.

Here's the first part of this step's program, in `src/main.cpp`:

```cpp
int addFive(int x) {
    return 5 + x;
}
```

The `int` before the name is the return type. It says the function gives back an `int`. The `return` statement sends the value back to the caller, and it also ends the function at that point. Nothing after a `return` runs.

The program calls the function and uses its result:

```cpp
int res = addFive(3);
std::cout << res << "\n";
```

The output is `8`. The call `addFive(3)` is replaced by its result, 8, which is then stored in `res`. A function call can appear anywhere a value of its return type can appear, so you can print it, store it, or put it inside another expression.

A function that gives nothing back uses `void` as its return type, as the first step did. `void` means there's no result to use, so `greet()` can't be the right-hand side of an assignment.

### Overloading

The program has two functions called `add`:

```cpp
int add(int x, int y) {
    return x + y;
}

double add(double x, double y) {
    return x + y;
}
```

C++ allows this, because the parameters are different. When you call `add`, the compiler looks at the arguments and picks the version that matches them:

```cpp
int whole = add(8, 5);
double decimal = add(4.3, 6.26);
```

The first call passes `int` values, so the `int` version runs and returns 13. The second passes `double` values, so the `double` version runs and returns 10.56. The output is:

```
Int: 13
Double: 10.56
```

Overloads must differ in their parameters. Two functions that differ only in their return type can't be overloaded, because the call `add(8, 5);` would give the compiler no way to choose, and it would reject the code.

---

### Quiz

*These questions are written for this course.*

````quiz
What happens to the statements after a `return` in a function?
○ They run, and then the function returns.
→ Not quite. return ends the function at that point.
◉ They don't run, because the function has already finished.
→ Yes. return leaves the function immediately.
○ They run only if the function has no return value.
→ Not quite. A return always ends the function, whatever its type.
````

````quiz
Which pair of functions can be overloaded?
○ int f(int x) and double f(int x)
→ Not quite. They differ only in their return type, so a call can't tell them apart.
◉ int f(int x) and double f(double x)
→ Yes. Their parameters differ, so the compiler can choose between them.
○ int f(int x) and int f(int x) with the same body.
→ Not quite. Two functions with identical parameters can't coexist, because the call would have no way to choose between them.
````

---

### Try it in the runner

Call `add(8, 5.0)`, which passes an `int` and a `double`, and predict which overload is chosen. Then press **Run**. You might expect the `double` version, but both overloads need one conversion to match the arguments, so the compiler can't prefer either one. It refuses the call as ambiguous. Change `5.0` to `5` to see the call work again.

---

A function can take values in and give a result back, and overloading lets one name serve several types. The next step uses arrays, which are harder to pass to a function than a single value, and the size of the array becomes something the function has to be told.
