## Homework: Sort by length

Sort a list of words from shortest to longest, using a lambda as the comparison. Words of the same length should keep the order they had in the list.

The program should:

* create a `std::vector<std::string>` holding "pear", "fig", "banana", and "kiwi", in that order
* sort it with `std::stable_sort`, passing a lambda that returns true when the first word is shorter than the second
* print `By length:` followed by each word, with a space before each one

The lambda compares lengths, using `size()` on each `std::string`. `std::stable_sort` takes the same arguments as `std::sort`, but it keeps the original order of values that compare as equal.

### What to check

The output should be:

```
By length: fig pear kiwi banana
```

"pear" and "kiwi" both have four letters, and "pear" came first in the list, so it stays first. That's the stability this exercise is testing. Try `std::sort` in its place, and see whether the order of those two words is guaranteed.

### Extensions

* Change the lambda so that equal lengths are ordered alphabetically, and check the output.
* Write the same comparison as a named function, and explain why the lambda is the better choice for a rule used only once.

---

*This exercise is not from the book. It practices the ideas in Chapter 20, with the sorting from Chapter 16.*
