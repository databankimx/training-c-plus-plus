## Parameters

A function that always does the same thing is limited. Most functions need information from the code that calls them, and parameters are how that information gets in. A parameter is a variable named in the function's brackets, and the value passed when the function is called is its argument.

Here's the program for this step, in `src/main.cpp`:

```cpp
void introduce(std::string fname, int age) {
    std::cout << fname << " is " << age << " years old.\n";
}
```

The function has two parameters, `fname` and `age`, each with a type. The call supplies the arguments in the same order:

```cpp
introduce("Scott", 53);
```

Press **Run**. The output is:

```
Scott is 53 years old.
```

Inside the function, `fname` holds "Scott" and `age` holds 53. The function doesn't know or care where those values came from. Calling it with other arguments gives different output, from the same code.

The arguments must match the parameters in number and type. Passing the arguments in the wrong order, such as `introduce(53, "Scott")`, fails to compile, because 53 can't be used as a string.

### Default values

A parameter can have a default value, which is used when the caller leaves that argument out:

```cpp
void welcome(std::string country = "United States") {
    std::cout << "The country is: " << country << "\n";
}
```

The program calls it twice:

```cpp
welcome();
welcome("Mexico");
```

The output is:

```
The country is: United States
The country is: Mexico
```

The first call passes nothing, so the default is used. The second call passes "Mexico", which replaces the default for that call only. Defaults are useful when most callers want the same value, and a few want something else.

There's one rule to remember. Once a parameter has a default, every parameter after it needs one too. The compiler can't work out which argument goes where if a parameter with a default is followed by one without.

---

### Quiz

*These questions are written for this course.*

````quiz
In `void introduce(std::string fname, int age)`, what is `fname`?
○ An argument.
→ Not quite. The argument is the value passed in, such as "Scott".
◉ A parameter.
→ Yes. The parameter is the name the function uses for the value it receives.
○ A return value.
→ Not quite. A return value is what a function sends back, and this one returns nothing.
````

````quiz
Which declaration is valid?
○ void f(int a = 1, int b);
→ Not quite. Once a parameter has a default, the parameters after it need defaults too.
◉ void f(int a, int b = 1);
→ Yes. The defaulted parameter comes last, so every argument is unambiguous.
○ void f(int a = 1, int b = 2, int c);
→ Not quite. The parameter c has no default, and it follows parameters that do.
````

---

### Try it in the runner

Call `introduce` with its arguments in the wrong order, as `introduce(53, "Scott")`, and press **Run**. Read the error message, and look for the argument the compiler complains about. Then put the arguments back in the right order.

Then add a second parameter to `welcome`, such as `int visits`, with no default, and see what the compiler says. It should refuse, because a parameter without a default can't follow one that has a default.

---

Parameters let one function handle many cases. The next step covers the other half of a function's interface: the value it sends back to the caller.
