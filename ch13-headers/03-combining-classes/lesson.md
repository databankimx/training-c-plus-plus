## Combining classes across files

This step puts the chapter together. Three classes live in three pairs of files, and one of them is built from the other two. Each class is small, and each file does one job. The program is spread across files, but the design is still the one from the classes chapter: an `ElectricCar` is a `Car`, and it has a `Battery`.

The relationships are the same ones the tutorial's single-file version used, and the files make them visible:

* `ElectricCar.h` includes `Car.h`, because the class inherits from `Car`.
* `ElectricCar.h` includes `Battery.h`, because the class holds a `Battery` as a member.

Here's the class header that does both:

```cpp
class ElectricCar : public Car {
public:
    ElectricCar(std::string makeName, std::string modelName, int yearMade, int charge = 0);
    void charge(int amount = 0);
    void showCharge() const;
    void display() const;

private:
    Battery battery;
};
```

Inheritance is written with a colon and `public Car`. The `battery` member is a `Battery` variable, which is built when the `ElectricCar` is built.

### The base constructor

The constructors chapter left one form unexplained, and this step uses it. The constructor of `ElectricCar` passes its arguments to the base class:

```cpp
ElectricCar::ElectricCar(std::string makeName, std::string modelName, int yearMade, int charge)
    : Car(makeName, modelName, yearMade) {
    if (charge > 0) {
        battery.recharge(charge);
    }
}
```

The colon introduces the base class's constructor, which runs first, before the body. `Car` has to be built before its derived part can be set up, so the arguments for `Car` are written here. The body then runs for the parts that belong to `ElectricCar`: it gives the battery an initial charge when one is given.

The member `battery` doesn't appear after the colon, because it has no arguments to pass. Its own constructor runs with its default of 100 capacity.

### What the program prints

Press **Run**. The output is:

```
Make: Ford
Model: Escort
Year: 1986

Make: Nissan
Model: Leaf
Year: 2015

Charge: 25
Capacity: 100

Charge: 50
Capacity: 100

Charge: 100
Capacity: 100

```

The `ElectricCar`'s `display` runs the `Car` part first, through `Car::display()`, and then prints the battery. Each `charge` call changes the battery and nothing else. The final `charge()` with no argument fills the battery, which is the rule from the last step.

---

### Quiz

*These questions are written for this course.*

````quiz
In `ElectricCar(...) : Car(makeName, modelName, yearMade) { ... }`, what does the part after the colon do?
○ It calls Car's display method.
→ Not quite. display is not called by the constructor.
◉ It passes the arguments to the base class's constructor, which runs before the body.
→ Yes. The base part is built first, so its arguments are given here.
○ It declares a new member called Car.
→ Not quite. Car is the base class, and nothing new is declared.
````

````quiz
Why does `ElectricCar.h` include both `Car.h` and `Battery.h`?
○ Because headers must include every header in the program.
→ Not quite. A header includes only what it needs to declare its own class.
◉ Because ElectricCar inherits from Car and holds a Battery, so both must be declared.
→ Yes. The compiler needs both classes' declarations to build ElectricCar.
○ Because one of them is a system header.
→ Not quite. Both are the course's own headers.
````

---

### Try it in the runner

Call `eCar.charge(200)` and predict the charge shown afterwards. The battery is capped at its capacity of 100, so the output is `Charge: 100`.

Then call `eCar.charge(-5)` and predict the result. The battery has no check for a negative amount, so the charge drops to 95. That's a real weakness of the class, and a good prompt for thinking about where validation belongs.

---

Three classes, three pairs of files, and a clear picture of which class depends on which. The summary covers the chapter's file rules, and the homework builds a small multi-file program of your own.
