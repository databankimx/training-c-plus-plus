## Homework: Word totals

Print each word and its count from a `std::map`, then print the total of all the counts. Use structured bindings for the loops, so each element is unpacked into named parts.

The program should:

* create a `std::map<std::string, int>` holding "pear" with 5, "apple" with 3, and "fig" with 2, in that order
* loop over the map with `for (const auto& [word, count] : counts)`, printing each word and its count on one line, separated by a space
* add the counts together in a second loop, which also uses structured bindings, and print `Total: ` followed by the sum

### What to check

The output should be:

```
apple 3
fig 2
pear 5
Total: 10
```

The map sorts its keys, so the words come out alphabetically, even though "pear" was inserted first.

### Extensions

* Add a second map, of the same type, and print the words that appear in both. Use a structured binding for the key, and a lookup with `find` or `count` for the second map.
* Change the loop to take the value by copy, `auto [word, count]`, and explain why `const auto&` is the better choice for a map of strings.

---

*This exercise is not from the book. It practices the ideas in Chapter 25, with the maps from Chapter 14.*
