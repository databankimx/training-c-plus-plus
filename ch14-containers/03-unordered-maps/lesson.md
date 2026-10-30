## Unordered maps

The map from the last step keeps its entries sorted, and that costs something. Finding a key in a `std::map` takes a number of comparisons that grows with the logarithm of the number of entries. For most programs that's fast enough, and the sorted order is useful. Sometimes it isn't enough, and a program has many lookups, with no need for any particular order. That's where `std::unordered_map` comes in.

Here's the program for this step, in `src/main.cpp`. It's the word count from the last step, with one change to the type:

```cpp
std::unordered_map<std::string, int> counts;
```

The header is `<unordered_map>`, and the rest of the code is the same. `counts[word]++` works in the same way, `count` tests for a key in the same way, and `size` reports the number of distinct words.

Press **Run**. The output is:

```
Distinct words: 3
apple: 3
pear: 2
fig: 1
kiwi is not in the map
```

The program prints only single lookups, not a loop over the whole table. That's deliberate, and the next section explains why.

### What makes it fast

An `unordered_map` is a hash table. It uses a function, called a hash, to turn each key into a number, and that number tells the table where to look for the key. Finding a key then means computing its hash and checking the few entries stored there, rather than comparing the key with many others. On average, a lookup takes about the same time however many entries the table holds. Computer scientists describe this as constant time, and the efficiency chapter explains what that means and where it stops being true.

### What it gives up

The table has no order. A loop over an `unordered_map` visits the entries in whatever order the table happens to hold them, and that order is not guaranteed. It can change when the number of entries grows and the table is rebuilt, and it can differ between compilers and library versions. A program whose output must be the same every time should not print an unordered map directly. Sort the results first, or use a `std::map`.

The same applies to tests. A test that compares printed output from an unordered map may pass on one machine and fail on another, even with unchanged code.

### Choosing between them

Use `std::map` when you need the entries in key order, or when the keys have an ordering that matters, such as dates. Use `std::unordered_map` when lookups dominate, the order doesn't matter, and the number of entries is large enough that speed matters. For a small number of entries, the difference is rarely noticeable, and the sorted map is often the clearer choice.

---

### Quiz

*These questions are written for this course.*

````quiz
Which header provides `std::unordered_map`?
○ <map>
→ Not quite. <map> provides the ordered std::map.
◉ <unordered_map>
→ Yes. The unordered container has its own header.
○ <hash>
→ Not quite. There's no standard header by that name for this container.
````

````quiz
Which statement about the order of an `unordered_map` is true?
○ Entries are always in the order they were inserted.
→ Not quite. Insertion order isn't kept.
◉ The order is not guaranteed, so output that must be stable should be sorted first.
→ Yes. The table's layout decides the order, and it can change.
○ Entries are always sorted by key.
→ Not quite. That's the std::map guarantee, not this container's.
````

---

### Try it in the runner

Add a loop that prints every entry of `counts`, and press **Run**. Then predict whether the order would be the same on a different compiler, or with more words added. The honest answer is that it might not be. You can't depend on the order, so any test or report that needs a fixed order has to sort the results first, or use a `std::map` instead.

---

An `unordered_map` trades order for speed on lookups, and it's a hash table underneath. The next step puts it beside the other containers in the choosing guide.
