## Homework: Shapes

Write a small set of shape classes, and a function that prints any shape's area without knowing which shape it is.

The program should:

* define a base class `Shape` with a `virtual` method `area`, which takes no parameters, is `const`, and returns 0.0
* define `Rectangle`, derived from `Shape`, with `double` members `width` and `height`, a constructor that takes both, and an `area` that overrides the base method
* define `Circle`, derived from `Shape`, with a `double` member `radius`, a constructor that takes it, and an `area` that overrides the base method, using 3.14159 for pi
* define `printArea`, which takes a `const Shape&` and prints `Area: ` followed by the area with two decimal places
* in `main`, call `printArea` with a `Rectangle` of width 3 and height 2, a `Circle` of radius 1, and a plain `Shape`

Use `std::fixed` and `std::setprecision(2)` before printing.

### What to check

The output should be:

```
Area: 6.00
Area: 3.14
Area: 0.00
```

The important part is that `printArea` is written once, for `Shape`, and works for all three. If the first two lines are both `0.00`, the `virtual` keyword is missing from the base method.

### Extensions

* Add a `Triangle` class with a base and a height, and check that `printArea` works for it without any change to `printArea`.
* Use `override` on each replacement, then misspell `area` in one of the derived classes, and read the compiler's message. Explain what the error prevents.

---

*This exercise is not from the book. It practices the ideas in Chapter 12.*
