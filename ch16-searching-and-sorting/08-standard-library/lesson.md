## The standard library sort and search

In real programs, you almost never write the sort yourself. The standard library provides sorting and searching in `<algorithm>`, and they're written and tuned by people who spend their time on exactly this problem. The earlier steps in this chapter taught you how the sorts work, which is what you need to choose and use them well. This step shows the library versions.

### Iterators

The library functions don't take a vector directly. They take a range, marked by two iterators. An iterator points at a position in a container, and it's the general way the library refers to positions, whatever the container is. The two that matter here are:

* `values.begin()`, which points at the first element
* `values.end()`, which points one place past the last element

A range runs from `begin()` up to, but not including, `end()`. So `std::sort(values.begin(), values.end())` sorts every element. You'll meet iterators again in the containers and algorithms chapters, where they're used throughout the library. The vectors step used `begin() + 1` to mean the second element, which is the same idea.

### Sorting

Here's the library sort, from `src/main.cpp`:

```cpp
std::vector<int> small = {14, 3, 19, 7, 1, 12, 20, 5, 16, 9, 2, 17, 6, 11, 18, 4, 13, 8, 15, 10};
std::sort(small.begin(), small.end());
```

That's the whole call. It sorts the 20-value list from the sorting steps into 1 through 20. The library doesn't count its steps for you, and it doesn't show them, so this step has no visualizer. The trace of a library sort would be the library's own work, which is not something to step through.

Press **Run**. The output begins:

```
Short list: 20 values
Sorted: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
```

The timing list is the same -1,000 to 1,000 shuffle as before. It's sorted in one call, and the output checks the result with `std::is_sorted`, which reports whether every value is in order from the first to the last.

### Searching a sorted range

`std::binary_search` answers a yes or no question about a sorted range, using the binary search from the previous steps. `std::lower_bound` returns an iterator, the position of the first value that is not smaller than the target. For a value that's present, that's its position:

```cpp
bool present = std::binary_search(small.begin(), small.end(), 12);
auto position = std::lower_bound(small.begin(), small.end(), 12);
std::cout << "Search for 12: " << (present ? "present" : "absent") << " at index "
          << static_cast<long long>(position - small.begin()) << "\n";
```

Subtracting `small.begin()` from the iterator gives the index, as a count of places from the start. The cast makes it print as a plain number.

Press **Run**. The output for the short list is:

```
Search for 12: present at index 11
```

The value 12 is the twelfth value in the sorted list, so its index is 11. The timing list has the same kind of search, and its output reports both results:

```
Search for 737: present
Search for 5,000: absent
```

Both searches use `binary_search` on the long sorted list, so they take about eleven comparisons each, as the binary search step showed for a list of this size.

### Big-O analysis

Let n be the number of values.

**Sorting.** `std::sort` makes O(n log n) comparisons, and the standard requires that cost on average. Typical implementations use introsort, which begins as quick sort and switches to heap sort if the recursion grows too deep. That keeps the worst case at O(n log n) as well.

---

**Sorting space.** The sort works in place, so its extra space is small. Typical implementations use O(log n) for the recursion.

**Searching a sorted range.** `binary_search` and `lower_bound` make O(log n) comparisons, the same as the binary search step. Both need the range to be sorted; on an unsorted range, their answers are meaningless.

**Checking order.** `std::is_sorted` reads each value once, so it's O(n). It's a cheap check after sorting, and it's useful in tests.

So the library gives O(n log n) sorting and O(log n) searching on sorted data, with no algorithm of your own to get wrong. The trade-off the previous steps measured still holds: sorting costs O(n log n) once, and each later search is O(log n), which pays off when the list is searched many times.

### When to use the library

Use `std::sort` and `std::binary_search` by default. They're faster than most hand-written versions, and they've been tested far more than anything you'd write in a course. Write your own sort when you're learning how sorts work, as this chapter did, or when a special requirement, such as a rule for ordering that the library can't express, calls for it.

The library can also sort by a rule you supply. That's a comparison function, and it uses a feature the containers chapter will introduce, so it's left for later.

---

### Quiz

*These questions are written for this course.*

````quiz
What does `values.end()` refer to in a range?
○ The last element of the vector.
→ Not quite. The last element is one place before end().
◉ The position one place past the last element, which the range does not include.
→ Yes. A range runs from begin() up to, but not including, end().
○ The number of elements in the vector.
→ Not quite. That's size(). end() is a position, not a count.
````

````quiz
What must be true before `std::binary_search` gives a correct answer?
○ The range must hold only positive numbers.
→ Not quite. Binary search works with any values, as long as they're in order.
◉ The range must be sorted.
→ Yes. Binary search depends on the order to throw away half the range each time.
○ The range must have an odd number of values.
→ Not quite. The length doesn't matter, only the order.
````

---

### Try it in the runner

Search the sorted short list for 1 with `std::lower_bound`, and predict the index before you press **Run**. The value 1 is the smallest, so it sits at index 0. Then try searching for 21, which isn't in the list, and predict what `lower_bound` returns: the end of the range, which is index 20.

---

The library gives you tested sorting and searching, with the same costs you measured in this chapter. The chapter summary, the homework, and the chapter overview come next, and they bring the search and sort steps together.
