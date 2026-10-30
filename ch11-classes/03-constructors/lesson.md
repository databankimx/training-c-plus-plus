## Constructors

A constructor is a special function that runs when an object is created. Its job is to set the object's members, so that every object starts in a valid state. It's declared with the class's name and no return type, and it takes whatever arguments the object needs to be built.

Here's the class for this step, in `src/main.cpp`. The constructor is declared in the class and defined below it:

```cpp
class Car {
public:
    Car(std::string mk, std::string mod, int yr);

    std::string brand;
    std::string model;
    int year;
    // ...
};

Car::Car(std::string mk, std::string mod, int yr) {
    brand = mk;
    model = mod;
    year = yr;
}
```

The constructor's body copies its arguments into the members. Nothing else needs to happen, since the members are already declared.

Press **Run**. The output is:

```
1969 Ford Mustang
2014 Dodge Challenger
```

### Two ways to create an object

The program creates two cars in two forms:

```cpp
Car myCar1 = Car("Ford", "Mustang", 1969);
Car myCar2("Dodge", "Challenger", 2014);
```

The first form calls the constructor explicitly and stores the result. The second passes the arguments in parentheses after the variable's name, and is shorter. Both create an object and run the constructor, so they're equivalent. Most code uses the second form.

### Why the constructor matters

Without a constructor, a class gets a default one that takes no arguments, and its members start with whatever values they have. With a constructor that takes arguments, a `Car` can't be created without a brand, model, and year. The compiler refuses any attempt to create one without them, so an incomplete car can't exist.

### Brace initialization with a constructor

The structures chapter used `Settings b{"Scott", 9, true};`, which set the members in order. A class with a constructor works differently: the braces call the constructor with those values, so the constructor's rules apply. The try in this step shows the result. The constructor takes three arguments, so a list of three values matches it. A class with a constructor doesn't accept a list that the constructor doesn't match.

### Passing arguments to a base class

When a class inherits from another, its constructor has to build the base part first. The colon after the constructor's parameter list names the base class, and passes it the arguments it needs:

```cpp
class Car {
public:
    Car(std::string mk, std::string mod, int yr);
    // ...
};

class ElectricCar : public Car {
public:
    ElectricCar(std::string mk, std::string mod, int yr)
        : Car(mk, mod, yr) {
        // the setup for ElectricCar itself goes here
    }
};
```

The base constructor runs first, with the values after the colon, and then the body of the derived constructor runs. The body can rely on the base part already being complete. If the derived class has no constructor of its own, the base's constructor is called in the same way, by the compiler, with no arguments, so the base must have a constructor that takes none.

You'll see this form in the combining-classes step of the headers chapter, where `ElectricCar` passes its make, model, and year to `Car`.

### A constructor isn't a method

A constructor is called by creating an object, not by calling `myCar.Car(...)`. It runs once per object, and it doesn't return a value. Methods are called on existing objects, and they can be called many times. The two look similar, since both are functions inside a class, but their jobs are different.

---

### Quiz

*These questions are written for this course.*

````quiz
What does a constructor have as its return type?
○ int
→ Not quite. A constructor returns nothing at all, and has no return type.
◉ None. It has no return type, and its name is the class name.
→ Yes. A constructor's name is the class name, and it returns nothing.
○ void
→ Not quite. A constructor doesn't have a return type, even void. It isn't called like a function that returns void.
````

````quiz
When does a constructor run?
○ Each time a method is called.
→ Not quite. Methods don't run the constructor.
◉ When an object of the class is created.
→ Yes. Creating the object calls its constructor, once.
○ When the program ends.
→ Not quite. Constructors run at creation. Destruction is a different job.
````

---

### Try it in the runner

Add `Car myCar3{"Fiat", "500", 2010};` to `main`, with a line to print it, and predict whether it compiles. It does, because the braces call the three-argument constructor. Then try `Car myCar4{"Fiat"};`, with only one argument, and press **Run**. The build fails, since no constructor takes one argument.

---

A constructor sets an object's members when the object is created, so each object starts in a known state. The next step restricts access to members, so that the only way to change an object is through the functions the class provides.
