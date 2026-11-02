## Pointers

A reference is another name for a variable, and it's fixed to that variable. A pointer is different. It's a variable that holds the address of another variable, as a value of its own. Because it's a value, a pointer can be changed to point somewhere else, and it can hold no address at all.

Here's the program for this step, in `src/main.cpp`:

```cpp
std::string food = "Pizza";
std::string* ptr = &food;   // ptr holds the address of food

std::cout << food << "\n";
std::cout << *ptr << "\n";
```

Press **Run**. The output is:

```
Pizza
Pizza
```

The declaration `std::string* ptr` says that `ptr` is a pointer to a `std::string`. The `&` on the right is the address-of operator. It gives the address of `food`, and that address is stored in `ptr`. The line doesn't print the address, because the number changes on every run, and nothing depends on knowing it.

The `*` in `*ptr` is the dereference operator. It means "the value at the address this pointer holds", so `*ptr` is `food`. Reading through the pointer gives the same text as reading `food` directly.

### Changing through a pointer

Assigning through a pointer changes the variable it points to:

```cpp
*ptr = "Hamburger";
std::cout << food << "\n";
```

The output is `Hamburger`. The pointer didn't change, and neither did its address. The value stored at that address did, and `food` is the value at that address.

### Pointers can be empty

A pointer that points at nothing is set to `nullptr`:

```cpp
std::string* empty = nullptr;
if (empty == nullptr) {
    std::cout << "The pointer is empty.\n";
}
```

The output is `The pointer is empty.` Dereferencing a null pointer, as in `*empty`, is undefined behavior, and usually crashes. Before you read through a pointer that might be empty, check it, as this `if` does.

### Pointer or reference

The two are easy to confuse, because both refer to another variable. A reference can't be empty, and it can't be changed to refer to something else. A pointer can be empty, can be reassigned to another address, and needs `*` to read the value it points to. Use a reference when the thing refers to something that always exists. Use a pointer when the target might change or might be missing.

---

### Quiz

*These questions are written for this course.*

````quiz
What does `*ptr` mean, when `ptr` holds the address of `food`?
○ The address of food.
→ Not quite. The address is what ptr holds. The star gives the value at that address.
◉ The value stored in food.
→ Yes. The dereference operator reads the value at the address the pointer holds.
○ A new copy of food.
→ Not quite. Dereferencing reads or changes the original variable.
````

````quiz
Which statement is true of a pointer that is `nullptr`?
○ It points to the first variable in the program.
→ Not quite. A null pointer points to nothing.
◉ It must be checked before it is dereferenced.
→ Yes. Dereferencing a null pointer is undefined behavior.
○ It can't be changed later.
→ Not quite. A pointer can be given a new address at any time.
````

---

### Try it in the runner

Change the value through `ptr` to `"Salad"`, and predict what `food` shows before you press **Run**. It shows `Salad`, since the pointer's target is `food`.

Then remove the `if` check around `empty`, and add a line that reads `*empty`. Predict what happens. The program may crash or print garbage, since there's no value at a null address. That's why the check is needed. Remove the line before you continue.

---

A pointer holds an address, and `*` reads or changes the value at that address. The next step uses pointers with arrays, where the connection you saw in the functions chapter becomes clear.
