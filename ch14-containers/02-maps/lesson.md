## Maps

A vector finds a value by its position. Often a program needs to find a value by a name instead: a word's count, a student's grade, or a price for an item. A `std::map` stores pairs, where each value is found through its key.

Here's the program for this step, in `src/main.cpp`. It counts the words in a list:

```cpp
std::map<std::string, int> counts;
std::string words[] = {"apple", "pear", "apple", "fig", "pear", "apple"};

for (const std::string& word : words) {
    counts[word]++;
}
```

The type `std::map<std::string, int>` names the key type first, then the value type. Reading `counts[word]` gives the value stored under that word, and `++` adds one to it. The first time a word appears, its entry doesn't exist yet, and the map creates it with the value 0 before the increment, so the count starts at one.

Press **Run**. The output is:

```
apple: 3
fig: 1
pear: 2
apple appears 3 times
kiwi is not in the map
```

### Sorted by key

The map keeps its entries sorted by key. The loop prints `apple`, `fig`, and `pear`, in alphabetical order, whatever order the words were added in. That's a useful property, and it's the reason a map prints the same way every time.

The loop uses `auto`, which tells the compiler to work out the type of `entry` from the map itself. Each entry is a pair, so `entry.first` is the key and `entry.second` is the value. You'll see `auto` in many loops over containers, since writing out the full type is often long.

### Looking up a key

`counts["apple"]` reads the value for a key. If the key is missing, `[]` creates it, which is easy to forget. The program avoids that surprise for `kiwi` by using `count`:

```cpp
if (counts.count("kiwi") == 0) {
    std::cout << "kiwi is not in the map\n";
}
```

`count` returns 1 if the key is present and 0 if it isn't, and it doesn't change the map. Use it when you want to test for a key without adding one.

### Map or vector

Use a vector when the position of a value matters, or when you're working through values in order. Use a map when you're looking up a value by a name or other key. A map of word counts answers "how many times does this word appear?" in one step, where a vector would need a search.

---

### Quiz

*These questions are written for this course.*

````quiz
What happens when `counts["kiwi"]` is read and `kiwi` isn't a key yet?
○ It's an error, and the program stops.
→ Not quite. A map creates the missing entry, so no error is raised.
◉ The entry is created with the value's default, which is 0 for an int.
→ Yes. Reading with [] inserts a missing key, so count doesn't see it afterwards.
○ It returns the value of the last key in the map.
→ Not quite. A missing key is not replaced with another entry's value.
````

````quiz
In what order does a range-based loop over a map visit its entries?
○ The order the entries were added.
→ Not quite. The map sorts its entries by key, whatever the insertion order.
◉ Sorted by key.
→ Yes. Keys are kept in sorted order, so the output is the same every time.
○ Reverse alphabetical order.
→ Not quite. The default order for a map's keys is ascending.
````

---

### Try it in the runner

Change `counts["apple"]` on the line that prints it to `counts["kiwi"]`, and press **Run**. Predict whether `kiwi is not in the map` still prints. It doesn't: reading `counts["kiwi"]` added the key with the value 0, so `count` now finds it. Then change the line back.

---

A map stores values under keys and keeps them sorted. Together with vectors, it covers most of the containers you'll use day to day. The next step puts the two side by side, with a short guide to choosing between them.
