## Solution: Shapes

The base class declares `area` as `virtual`, so a call through a `const Shape&` uses the derived version. `printArea` takes the base by reference and calls `shape.area()`, which is why it works unchanged for a rectangle, a circle, and a plain shape.

Each derived class overrides `area`, and `override` makes the compiler confirm that the function replaces a virtual one. That's the check the extension asks you to test with a misspelled name. Without it, a misspelled `aera()` would compile as a new function, and `printArea` would keep calling the base version, printing 0.00 with no error.

The base's `area` returns 0.0. A plain `Shape` has no size, so its area is zero, and printing that is correct rather than an error.

The circle uses a `const` local for pi, as the functions chapter's area exercise did, so the constant has a name and can't be changed by accident.
