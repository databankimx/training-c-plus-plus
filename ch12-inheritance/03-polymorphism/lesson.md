## Polymorphism

Polymorphism means "many forms". In C++, it's the ability to call one function through a base-class reference and have the right version run for the object actually passed in. The caller writes one line, and the object decides what that line does.

The program for this step, in `src/main.cpp`, shows the three parts it needs. The base class marks its function `virtual`:

```cpp
class Animal {
public:
    virtual void sound() const {
        std::cout << "The animal makes a sound...\n";
    }
};
```

Each derived class replaces the function, and says so with `override`:

```cpp
class Pig : public Animal {
public:
    void sound() const override {
        std::cout << "The pig says: oink oink!\n";
    }
};
```

And a function takes a reference to the base:

```cpp
void makeSound(const Animal& animal) {
    animal.sound();
}
```

Press **Run**. The output is:

```
The animal makes a sound...
The pig says: oink oink!
The dog says: bow wow!
```

The three calls all have the same form, `makeSound(something)`, and the function inside calls `sound()` on whatever it was given. The object decides which version runs.

### Static and dynamic type

A reference has two types. Its declared type, `const Animal&`, is fixed when the code is written. The type of the object it refers to, `Pig` or `Dog`, is known only when the program runs. `virtual` tells the compiler to look up the function using the object's real type, at run time, instead of the reference's declared type.

Without `virtual`, the compiler chooses `Animal::sound` at compile time, from the declared type. Every call would print the animal message, whatever object was passed in. That's the trap the tutorial's example falls into, and the Try shows it.

### What override does

`override` asks the compiler to check that the function really replaces a `virtual` function in a base class. If you misspell the name, or give it a different parameter list, the compiler reports an error, rather than quietly creating a new function that nothing calls. Use `override` on every replacement.

### Pass by reference

The parameter is a reference, not a copy. A copy of a `Pig` passed as an `Animal` would keep only the `Animal` part, and the pig's own version would be lost. This is called slicing, and it's the reason polymorphic parameters should be references or pointers. The `const` promises that `makeSound` won't change the animal.

---

### Quiz

*These questions are written for this course.*

````quiz
What does `virtual` change about a function?
○ It makes the function run faster.
→ Not quite. Its effect is on which version is called, not on speed.
◉ It lets calls through a base reference use the version in the object's real class.
→ Yes. The lookup happens at run time, using the object's real type.
○ It makes the function private.
→ Not quite. virtual says nothing about access.
````

````quiz
What does `override` do?
○ It removes the base class's version of the function.
→ Not quite. The base version still exists, and is used by objects that don't replace it.
◉ It asks the compiler to check that the function really replaces a virtual function.
→ Yes. A misspelled or mismatched replacement becomes a compile error.
○ It allows the function to be called without an object.
→ Not quite. override says nothing about how the function is called.
````

---

### Try it in the runner

Remove `virtual` from `Animal::sound`, and remove `override` from the two derived functions. Predict the output of `makeSound(pig)` before you press **Run**. It prints `The animal makes a sound...`, since without `virtual`, the compiler chooses the base version from the reference's declared type.

Then put `virtual` back on `Animal::sound`, and remove only the `override` keyword from `Pig::sound`. The build still succeeds, and `makeSound(pig)` prints the pig's message again. `override` is optional, but it's the check that catches a mistake. Restore both keywords before you continue.

---

Polymorphism lets one call do different work for different objects, and it depends on `virtual` and a reference to the base. The summary covers the chapter's inheritance rules, and the homework applies them to a small program.
