## Structures as variables

A variable holds one value. Often a program needs several values that belong together: a car has a brand, a model, and a year, and those three values travel as one thing. A structure groups them under one name, and each value inside it is a member.

Here's the program for this step, in `src/main.cpp`. The structure is declared once, at the top of the file:

```cpp
struct Car {
    std::string brand;
    std::string model;
    int year;
};
```

The declaration creates a new type, `Car`, in the same way `int` and `std::string` are types. It doesn't create any cars. It describes what a car contains: a brand, a model, and a year. Declare it outside `main`, so every function can use it.

Create a variable of the type, and set its members with a dot:

```cpp
Car myCar1;
myCar1.brand = "BMW";
myCar1.model = "X5";
myCar1.year = 1999;
```

Press **Run**. The output is:

```
BMW X5 1999
Ford Mustang 1969
```

Each car is one variable, and its members are reached through the dot. `myCar1.brand` is the brand of the first car, and `myCar2.year` is the year of the second. The two cars have the same members, but each car has its own values.

### Declaring the structure and the variables

Some tutorials show a structure declared inline, with its variables in the same statement. The result works, but the structure has no name, so no other variable or function can use the same type. Declare the structure with a name, as this step does, so you can create as many variables of it as you need, and pass it to functions.

### Members have their own types

Each member has its own type, and the compiler checks every assignment against it. `myCar1.year = "1999";` won't compile, since `year` is an `int`. The structure's declaration is the record of those types, so you can read it to see what each member expects.

---

### Quiz

*These questions are written for this course.*

````quiz
What does the declaration `struct Car { ... };` create?
○ A car, ready to use.
→ Not quite. It describes a car, but it doesn't create one.
◉ A new type, which variables of type Car can be made from.
→ Yes. The declaration names the type and lists its members.
○ A function that prints a car.
→ Not quite. A structure is data, not a function.
````

````quiz
How do you set the year of `myCar1`?
○ myCar1->year = 1999;
→ Not quite. The arrow is for pointers, and myCar1 is a variable.
◉ myCar1.year = 1999;
→ Yes. A dot reaches a member of a structure variable.
○ Car.year = 1999;
→ Not quite. The dot works on a variable, not on the type's name.
````

---

### Try it in the runner

Add a member called `color`, of type `std::string`, to `Car`. Then print `myCar1.color` without setting it, and predict the output before you press **Run**. It prints an empty line. A `std::string` member starts as an empty string, so an unset text member prints nothing.

Then set `myCar1.year` to `"1999"`, in quotes, and press **Run**. The build fails, because `year` is an `int`, and a string can't be stored in it.

---

A structure gives a name to a group of values, and each member has its own type. The next step passes structures to functions, and returns them from functions, which lets a program move a whole group of values at once.
