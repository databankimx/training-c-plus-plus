## Inheriting members

Many classes share most of their behaviour. A car is a kind of vehicle, and a sports car is a kind of car. Rather than writing the shared members again for each class, inheritance lets a class take on the members of another class, and add its own.

Here's the program for this step, in `src/main.cpp`. The base class comes first:

```cpp
class Vehicle {
public:
    std::string brand = "Ford";

    void honk() const {
        std::cout << "Toot, toot!\n";
    }
};
```

The derived class names its base after a colon:

```cpp
class Car : public Vehicle {
public:
    std::string model = "Mustang";
};
```

The words `: public Vehicle` mean that `Car` inherits the public members of `Vehicle`. A `Car` has `brand` and `honk()` without writing them again, and it adds `model` of its own.

Press **Run**. The output is:

```
Toot, toot!
Ford Mustang
Toot, toot!
Ford Mustang 180
```

`myCar.honk()` and `myCar.brand` come from `Vehicle`, and `myCar.model` comes from `Car`. The `SportsCar` class inherits from `Car`, which inherits from `Vehicle`, so `fast` has all three sets of members. Inheritance can continue down a chain of any length.

### The base and the derived class

The class that is inherited from is the base class, and the class that inherits is the derived class. A derived class is a more specific kind of its base. Every `Car` is a `Vehicle`, which is the test for whether inheritance fits: the sentence "a derived is a base" should be true.

### Inherited members are not copied

The derived class doesn't copy the base's members into its own text. It refers to them through the base, so a change to the base's behaviour appears in every class that inherits it. That's the reason inheritance is useful for shared behaviour, and the reason it's worth using carefully.

### The public keyword

`: public Vehicle` is an access level for the inheritance itself, and it means that the base's public members stay public in the derived class. The next step covers the other two levels, and what they mean for the members a derived class can use.

---

### Quiz

*These questions are written for this course.*

````quiz
Which statement describes inheritance correctly?
○ The derived class copies the base class's code into itself.
→ Not quite. The derived class refers to the base's members, rather than copying them.
◉ The derived class gets the base's public members, and can add its own.
→ Yes. A derived class is a more specific kind of its base.
○ The base class gets the derived class's members.
→ Not quite. Inheritance works the other way: the derived class takes on the base's members.
````

````quiz
In `class SportsCar : public Car`, which class's members can a SportsCar use?
○ Only its own members.
→ Not quite. It also gets the members of Car, and of Vehicle through Car.
◉ Its own, Car's, and Vehicle's public members.
→ Yes. Inheritance passes along the chain, so each class adds to the one above.
○ Only Vehicle's members.
→ Not quite. SportsCar also has the members of Car and its own.
````

---

### Try it in the runner

Add a method called `describe()` to `Vehicle` that prints `A vehicle.` Call it on `fast`, and predict whether `SportsCar` can use it. It can: `describe` is inherited through `Car`, and no change to `Car` is needed.

Then remove `public` from `: public Car` in the `SportsCar` declaration, and press **Run**. The build fails. Without `public`, the inheritance is private by default for a class, and `fast.honk()` is no longer accessible from `main`. Restore the keyword before you continue.

---

A derived class takes on the public members of its base, and can add its own. The next step covers the protected and private levels, and multiple base classes.
