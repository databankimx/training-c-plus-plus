## Solution: Library

The header for each class declares it, and the source file defines its functions. `Book.h` and `Library.h` both have guards, and neither has a `using namespace` line. `main.cpp` includes both headers, and the CMake file lists all three source files.

The order in `main` matters. `add` takes a `const Book&` and stores a copy in the array, so the checkout has to happen before the book is added. Checking out `emma` after `lib.add(emma)` would change only the original, and `printAll` would show it as available. That's the copy behaviour from the structures chapter, now seen across files.

`Library` holds its books in an array of three `Book` objects. Each one is built with the default constructor, so the array can exist before any book is added. The `used` count tracks how many slots are filled, and `printAll` stops at that count, rather than printing the empty slots.

For the first extension, the check belongs in `add`, since `add` is the only place that knows the capacity. `main` can ask whether a book was added, but the library should decide. A `bool` return from `add` would let the caller react to a full library, and is a reasonable next step.

The second extension is a small getter, `int count() const { return used; }`, declared in `Library.h` and defined in `Library.cpp` like the other methods.
