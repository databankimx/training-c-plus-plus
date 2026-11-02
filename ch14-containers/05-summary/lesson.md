## Summary: Containers

This chapter covered the standard containers that store collections of values.

* **`std::vector` grows as you add to it.** `push_back` adds an element, `size()` gives the count, and the vector keeps its order.
* **`at` checks the index.** `scores.at(i)` throws `std::out_of_range` for a bad index, where `scores[i]` reads past the end with undefined results.
* **`std::map` finds values by key.** `counts[key]` reads or creates the value, and `count(key)` tests for a key without adding one.
* **A map keeps its keys sorted.** A loop over a map visits entries in key order.
* **`std::unordered_map` trades order for lookup speed.** It's a hash table, and it has no guaranteed order, so output that must be stable needs sorting first.
* **Reading with `[]` inserts a missing key.** Use `count` when a lookup must not change the map.
* **Choose by the main job.** Use an array for a fixed size, a vector for an ordered list, and a map for lookups by key.
* **Containers can be combined.** A program often keeps one container for order and another for lookups.

### Check your understanding

*These questions are written for this course.*

````quiz
Which member tests whether a key is in a map, without adding it?
○ counts[key]
→ Not quite. Reading with [] creates a missing key, so it changes the map.
◉ counts.count(key)
→ Yes. count returns 0 or 1, and doesn't insert.
○ counts.size()
→ Not quite. size gives the number of entries, not whether a key is present.
````

````quiz
In what order does a loop over a `std::map` visit its entries?
○ The order they were inserted.
→ Not quite. A map keeps its entries sorted by key.
◉ Sorted by key.
→ Yes. The key order is part of the map's guarantee.
○ Random order.
→ Not quite. The order is fixed by the keys, so it's the same every time.
````

````quiz
Why use `at` rather than `[]` when the index comes from user input?
○ Because [] is slower.
→ Not quite. The reason is safety, not speed.
◉ Because at checks the index and throws an exception, where [] reads past the end.
→ Yes. A checked read turns a bad index into a catchable error.
○ Because [] isn't allowed on vectors.
→ Not quite. [] is allowed, but it doesn't check.
````
