## Shared pointers

Some objects have more than one owner, and no single owner can say when the object is no longer needed. A tree node is pointed to by its parent and by a cache, for example. `std::shared_ptr` handles that case. Each shared pointer is an owner, and the object is released when the last owner goes away.

Here's the program for this step, from `src/main.cpp`:

```cpp
std::shared_ptr<Resource> first = std::make_shared<Resource>("file D");
std::cout << "Owners: " << first.use_count() << "\n";

{
    std::shared_ptr<Resource> second = first;
    std::cout << "Owners: " << second.use_count() << "\n";
}

std::cout << "Owners: " << first.use_count() << "\n";
```

`std::make_shared` creates the object and the first owner. Copying a shared pointer creates another owner, and both point at the same `Resource`. The `use_count` function reports how many shared pointers own the object right now.

Press **Run**. The output is:

```
Acquire file D
Owners: 1
Owners: 2
Owners: 1
End
Release file D
```

The copy adds an owner, so the count goes to 2. When the block ends, `second` is destroyed, which removes its ownership, and the count drops back to 1. The object is still alive, because `first` still owns it. It's released only when `first` goes out of scope at the end of `main`, after `End`.

### The count is a hint, not a guarantee

`use_count` is useful for learning and for debugging. Don't write logic that depends on its exact value in a program with threads, since another thread can change the count between the check and the use. For the single-threaded programs in this course, it always matches the number of owners at that moment.

### Choosing a smart pointer

Use `std::unique_ptr` by default. It costs nothing extra, and it says that one owner is responsible for the object. Use `std::shared_ptr` only when the ownership really is shared, since it has to keep a count of its owners, which costs time and memory. A shared pointer that is used where a unique pointer would do hides the question of who owns the object.

### Shared pointers and cycles

Two objects that hold shared pointers to each other keep each other alive, and neither count ever reaches zero. That's a cycle, and it leaks both objects. The usual fix is a weak pointer, which refers to an object without owning it. Weak pointers are a topic for later, and it's enough to know the risk now.

---

### Quiz

*These questions are written for this course.*

````quiz
What does `use_count` report?
○ The number of objects of the type that exist.
→ Not quite. It counts owners of one particular object.
◉ The number of shared pointers that currently own the object.
→ Yes. Each copy of a shared pointer adds one owner.
○ The number of times the object has been used.
→ Not quite. It counts owners, not uses.
````

````quiz
When is a `std::shared_ptr`'s object released?
○ Each time a shared pointer is copied.
→ Not quite. Copying adds an owner and releases nothing.
◉ When the last shared pointer that owns it goes away.
→ Yes. The count reaches zero, and the object is deleted.
○ As soon as the first shared pointer is destroyed.
→ Not quite. Other owners may still hold the object, so it survives.
````

---

### Try it in the runner

Copy `first` into a second `shared_ptr` in its own block, then call `first.reset()` inside that block. Predict the owner count after the reset, and whether `file D` is released there. The count drops to 1, since the copy still owns the object, so nothing is released yet. The release happens when the copy goes out of scope.

---

A shared pointer releases its object when the last owner is gone, and `use_count` shows how many owners there are. The next step is the chapter summary, and then two homework exercises that use all three kinds of ownership.
