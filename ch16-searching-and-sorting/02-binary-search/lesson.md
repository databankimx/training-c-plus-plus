## Binary search

Linear search has to check every value in the worst case, because it knows nothing about where a value might be. A sorted list gives the search something to use. If the list is in order, checking one value tells you which half the target can be in, and the search can throw the other half away.

Here's the search, from `src/main.cpp`:

```cpp
int binarySearch(const std::vector<int>& values, int target, long long& comparisons) {
    int low = 0;
    int high = static_cast<int>(values.size()) - 1;
    while (low <= high) {
        int middle = (low + high) / 2;
        comparisons++;
        if (values[static_cast<std::size_t>(middle)] == target) {
            return middle;
        }
        if (values[static_cast<std::size_t>(middle)] < target) {
            low = middle + 1;
        } else {
            high = middle - 1;
        }
    }
    return -1;
}
```

The `low` and `high` indexes mark the part of the list still being searched. Each pass checks the middle value. If it matches, the search stops. If the middle is less than the target, the target must be in the upper half, so `low` moves past the middle. If the middle is more than the target, `high` moves below it. Either way, half of what was left is thrown away, and the loop goes around again. When `low` passes `high`, the range is empty and the target isn't in the list.

### The data

Binary search needs sorted data. The short list is in order, so you can see where each value is:

```cpp
std::vector<int> small = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
```

The value 7 sits at index 7. The long list holds every whole number from 0 to 1,000, in order. In both lists, each value sits at the index that matches it, so you can check the counts by hand. That's a feature of these lists, not a rule of binary search. Binary search works the same way on any sorted list, where the index and the value needn't match at all.

Press **Run**. The output is:

```
Sorted list: 12 values
Searching for 7: index 7 after 4 comparisons
Sorted list: 1,001 values
  for 737: index 737 after 10 comparisons (linear search: 738)
  for 5,000: NOT FOUND after 10 comparisons
```

### What the counts show

Searching for 7 checks four values: the middle of the whole list, then the middle of the part that's left, and so on, until it lands on index 7.

Finding 737 takes 10 comparisons. A linear search would check 738 values to reach the same place, since it has to pass every index before 737. The gap grows with the list. Doubling the length adds only one more comparison to a binary search, while it doubles the work for a linear one.

The count is the number of times the range can be halved before it's down to one value. For a list of about a thousand values, that's about ten. This growth is O(log n), and it's the reason binary search is so much faster on large sorted lists.

The search for 5,000 is outside the list, so it can't be found. It still takes 10 comparisons to show that the range is empty, which is the same cost as a found value near the end.

### The cost of sorting

Binary search is only fast when the list is sorted. Sorting takes work, and the next steps measure how much. The lesson for now is that searching a list many times is cheaper when it's sorted once, and that a single search on an unsorted list is still better done as a linear search.

### Big-O analysis

Let n be the number of values in the sorted list.

**Comparisons.** Each comparison halves the part still being searched, so the search ends after at most about log₂n + 1 comparisons. For 1,001 values, that's at most 10. The growth is O(log n).

---

**Best case.** If the middle value is the target, the search makes one comparison and stops. That's O(1).

**Space.** This version keeps only the low, high, and middle indexes, so its extra space is O(1). A recursive version would use one stack frame for each halving, which is O(log n) space. That's a real cost, and it's why the iterative form is usually preferred.

**The sort is extra.** Binary search only works on sorted data, so the total cost includes sorting the list first. Sorting takes at least O(n log n), as the next steps show, so one binary search on unsorted data is cheaper done as a linear search.

### Watch the search

The program writes `trace.js` for the short list. Press **Run** first, then press **Visualize**. Each bar is one value. The bars outside the range still being searched fade out, so you can see the list shrink. The amber bar is the middle being checked, and the green bar is the match.

Use **Next**, **Previous**, the slider, the arrow keys, or **Play** to move through the search. **Speed** sets how long each step stays on screen.

---

### Quiz

*These questions are written for this course.*

````quiz
What does binary search need that linear search doesn't?
○ A list with no duplicates.
→ Not quite. Duplicates don't stop either search, so this isn't the requirement.
◉ A list that is sorted, so that checking one value tells the search which half to keep.
→ Yes. The order is what lets the search throw half of the list away each time.
○ A list with a known length.
→ Not quite. Both searches can find the length of a list, so it's not what binary search needs.
````

````quiz
Finding a value in a list of 1,001 sorted values takes about ten comparisons. What is the growth of binary search?
○ O(n), the same as linear search.
→ Not quite. That's the growth of linear search, which checks each value in turn.
◉ O(log n), since each comparison halves the part still being searched.
→ Yes. Doubling the list adds only one more comparison.
○ O(n squared), since each comparison has to be repeated.
→ Not quite. Each comparison is made once, and the number of comparisons grows slowly.
````

---

### Try it in the runner

Search the sorted list for 12, and predict what the program prints and how many comparisons it makes before you press **Run**. The value isn't in the list, and the search ends when the range is empty, so the answer is `NOT FOUND` after 4 comparisons.

Then press **Visualize** on the trace for 7, and watch which half is thrown away at each step. Count the frames, and check that they match the four comparisons the program printed.

---

Binary search is far cheaper than linear search on a sorted list, and its cost grows with the logarithm of the length. It depends on the list being in order, which is what the sorting steps are for.
