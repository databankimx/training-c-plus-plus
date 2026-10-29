## Methods

A method is a function that belongs to a class. It's called on an object, and it can use that object's members directly, without the caller naming them. That's why a method reads more naturally than a free function that takes the object as a parameter.

Here's the class for this step, in `src/main.cpp`:

```cpp
class Car {
public:
    std::string brand;
    std::string model;
    int year;

    std::string name() const {
        return brand + " " + model;
    }

    std::string fullName() const;
};
```

Inside `name`, the members `brand` and `model` appear by name, with no object in front of them. The method works on whichever object it was called on, so `myCar.name()` uses `myCar.brand`, and another object's `name()` uses its own.

The `const` after the parentheses is a promise. It says that the method reads the object but doesn't change it. A `const` method can be called on any object, including one declared `const`, and the compiler checks that the method doesn't modify any member. Use `const` on every method that only reads.

### Defining a method outside the class

`fullName` is declared inside the class, and defined after it:

```cpp
std::string Car::fullName() const {
    return std::to_string(year) + " " + brand + " " + model;
}
```

The name `Car::fullName` says which class the method belongs to. The declaration in the class must match the definition exactly, including the `const`. Declaring a method in the class and defining it below is common in larger programs, because the class's layout is easy to read in one place.

Press **Run**. The output is:

```
Ford Mustang
1969 Ford Mustang
```

The two methods read the same members, and each formats them differently. `std::to_string` converts the year to text, so it can be joined with the other strings.

### Calling a method

The caller writes the object, a dot, the method name, and the parentheses:

```cpp
myCar.name()
```

Those parentheses are required, even when the method takes nothing. Without them, `myCar.name` names the method but doesn't call it, which is a mistake the compiler reports as an error.

---

### Quiz

*These questions are written for this course.*

````quiz
Inside a method, how does the code refer to the object's brand?
○ this.brand
→ Not quite. That form exists, but the course doesn't need it here: inside a method, the member name is enough.
◉ brand
→ Yes. Inside a method, the object's members can be named directly.
○ Car.brand
→ Not quite. Car is the class, and brand belongs to an object.
````

````quiz
What does the `const` after a method's parentheses promise?
○ That the method returns a constant value.
→ Not quite. It concerns what the method does to the object, not what it returns.
◉ That the method reads the object without changing it.
→ Yes. The compiler checks that a const method doesn't modify any member.
○ That the method can only be called once.
→ Not quite. A const method can be called any number of times.
````

---

### Try it in the runner

Remove `const` from both `name` and `fullName`, in the declaration and in the definition, and press **Run**. The program still builds, since `myCar` isn't `const`. Then keep the `const` in the declaration, and remove it only from the definition. The build fails, because a definition has to match its declaration exactly.

Restore the `const` before you continue.

---

A method is a function that belongs to a class, and it works on the object it's called on. The next step covers constructors, which set an object's members when it's created.
