## Structures in functions

A structure is most useful when it travels. A function can build one and return it, receive one and read it, or receive one by reference and change it. The rules are the same ones you saw for values in the functions chapter, with the structure taking the place of the single value.

Here's the program for this step, in `src/main.cpp`. It begins with a function that builds a car:

```cpp
Car makeCar(std::string brand, std::string model, int year) {
    Car car;
    car.brand = brand;
    car.model = model;
    car.year = year;
    return car;
}
```

The return type is `Car`, so the function gives back a whole car. The caller stores it like any other value:

```cpp
Car mine = makeCar("BMW", "X5", 1999);
```

### Passing a copy

The next function receives a car as a parameter:

```cpp
void describe(Car car) {
    std::cout << car.brand << " " << car.model << " " << car.year << "\n";
}
```

The parameter is an ordinary copy, as the functions chapter described. The function reads the members and prints them, and it has no way to affect the caller's car. For a structure with a few members, copying is cheap enough that this is the usual choice.

### Passing a reference

The next function changes the car it receives:

```cpp
void makeOlder(Car& car) {
    car.year -= 10;
}
```

The `&` makes `car` a reference, so `car.year -= 10` changes the year of the caller's car. After `makeOlder(mine);`, the year of `mine` is 1989. Use this form only when the function is meant to change the structure.

### Arrays of structures

The program then makes an array of two cars, and visits each one:

```cpp
Car cars[2] = {makeCar("Ford", "Mustang", 1969), makeCar("Fiat", "500", 2010)};
for (Car car : cars) {
    describe(car);
}
```

An array of structures works like any other array. The range-based `for` gives each element to `car` in turn, and each element is copied into it, so `describe` receives a copy of each car.

The output for the whole program is:

```
BMW X5 1999
BMW X5 1989
Ford Mustang 1969
Fiat 500 2010
```

---

### Quiz

*These questions are written for this course.*

````quiz
After `makeOlder(mine);`, which statement is true?
○ mine is unchanged, because makeOlder works on a copy.
→ Not quite. makeOlder takes a reference, so it works on mine itself.
◉ mine.year is 10 less than before, because the reference changes the caller's car.
→ Yes. The reference gives makeOlder access to mine.
○ A new car is created, and mine is replaced by it.
→ Not quite. The function changes the car it was given, and creates nothing new.
````

````quiz
Why is `describe` written with a copy of the car, rather than a reference?
○ Because references can't be used with structures.
→ Not quite. They can, and makeOlder uses one.
◉ Because describe only reads the car, and a copy makes it clear that nothing is changed.
→ Yes. A copy can't change the caller's structure, which is what describe needs.
○ Because copies are faster than references in every case.
→ Not quite. The difference is what the function may change, not speed.
````

---

### Try it in the runner

Change `describe` so its parameter is `Car& car`, and predict the effect on `makeOlder`. Nothing changes for `makeOlder`, since it already takes a reference. `describe` now refers to the caller's car, but it still doesn't change it, so the output is the same. The change is about intent: a reference suggests that the function might modify the car, and a copy promises that it won't.

Then remove the `&` from `makeOlder`, and predict the second line of output. It's `BMW X5 1999`, since the change happened to a copy.

---

A structure travels through a program as one value, and the parameter type decides whether a function may change it. The next step gives structures default values and brace initialization, so each variable starts in a known state.
