## Homework: Pair

A pair holds two values, which may be of different types. In this exercise, you write a class template with two type parameters, and use it with two different combinations of types.

The program should:

* write a class template `Pair` with two type parameters, `First` and `Second`, a constructor that takes one value of each, and two `const` member functions, `getFirst` and `getSecond`, that return them
* in `main`, create a `Pair<int, std::string>` holding 3 and "three", and print `Pair: ` followed by the first value, a space, and the second value
* create a `Pair<std::string, double>` holding "pi" and 3.14, and print it in the same form

### What to check

The output should be:

```
Pair: 3 three
Pair: pi 3.14
```

The two pairs are different types, so the compiler generates two classes from the one template. Each one returns the types it was given: an `int` and a `std::string` for the first pair, and a `std::string` and a `double` for the second.

### Extensions

* Write a `swapped` member function that returns a `Pair<Second, First>`, the same values in the opposite order. Predict the type of `swapped` for the first pair before you write it.
* Explain why `Pair<int, int>` is valid even though both parameters are the same type.

---

*This exercise is not from the book. It practices the ideas in Chapter 19.*
