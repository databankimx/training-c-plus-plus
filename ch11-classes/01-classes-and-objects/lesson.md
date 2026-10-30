## Classes and objects

A structure groups values. A class does the same, and it can also hold the functions that work on those values. The two are closely related in C++, and this step starts with the form that looks most like a structure, so the change is easy to follow.

Here's the program for this step, in `src/main.cpp`:

```cpp
class Car {
public:
    std::string brand;
    std::string model;
    int year;
};
```

The keyword is `class`, and the word `public:` sets the access level for the members that follow. Members marked `public` can be used from anywhere, which is what `main` needs here. The next steps make some members private.

A variable of the class is called an object. `Car carObj1;` creates one object, and each object has its own `brand`, `model`, and `year`:

```cpp
Car carObj1;
carObj1.brand = "BMW";
carObj1.model = "X5";
carObj1.year = 1999;
```

Press **Run**. The output is:

```
BMW X5 1999
Ford Mustang 1969
```

### Class and struct

In C++, a `struct` and a `class` differ in one way: a struct's members are public by default, and a class's members are private by default. Everything else works the same. The `public:` line in this step makes the class behave exactly like the structure from the last chapter. From here on, the class is the tool to reach for when a type has behaviour as well as data, and the choice between the two is a matter of style.

### Objects are independent

Each object holds its own values. Changing `carObj1.year` leaves `carObj2.year` alone. This is the same independence that copies of structures had in the last chapter, and it's why one class can describe many cars.

---

### Quiz

*These questions are written for this course.*

````quiz
What is a class's default access level for its members?
○ public
→ Not quite. That's the default for a struct, not a class.
◉ private
→ Yes. A class's members are private unless you say otherwise.
○ protected
→ Not quite. Protected members aren't the default for a class.
````

````quiz
What is `carObj1` in `Car carObj1;`?
○ A class.
→ Not quite. The class is Car, and carObj1 is one object of it.
◉ An object of the class Car.
→ Yes. Each variable of a class is an object of that class.
○ A method.
→ Not quite. Methods are functions that belong to a class, and carObj1 holds data.
````

---

### Try it in the runner

Change the access label at the top of the class from `public:` to `private:`, and press **Run**. Predict whether `main` still compiles. It doesn't: the members are private, so `main` can't read or write them. The build fails with an error that names the member. Change the label back before you continue.

---

A class groups data and gives each variable of it a name: an object. Its access labels decide which parts of the program can reach that data. The next step adds functions that belong to the class, which are called methods.
