## Homework: Smallest of

Write a function template that returns the smallest value in a `std::vector`, and use it for numbers and for strings.

The program should:

* write `template <typename T> T smallestOf(const std::vector<T>& values)`, which assumes the vector has at least one value, starts with the first value as the smallest, and compares each later value with it
* in `main`, create a `std::vector<int>` holding 5, 2, and 9, and print `Smallest number: ` followed by the result
* create a `std::vector<std::string>` holding "pear", "apple", and "fig", and print `Smallest word: ` followed by the result

### What to check

The output should be:

```
Smallest number: 2
Smallest word: apple
```

The same template produces both results. The string comparison is alphabetical, so "apple" comes before "fig" and "pear".

### Extensions

* Add a function template that returns the largest value, and check that it works for both vectors.
* Call `smallestOf` with an empty vector. Decide what it should return, since the function as written would read past the end, and explain why a template doesn't solve that problem for you.

---

*This exercise is not from the book. It practices the ideas in Chapter 19, with the vectors from Chapter 14.*
