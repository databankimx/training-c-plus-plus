## Merge sort

Merge sort uses a different idea from the sorts so far. Instead of working through the whole list at each step, it splits the list in half, sorts each half the same way, and then combines the two sorted halves. Each half is split again until a piece holds a single value, which is already sorted. The combining step is where the work happens.

This is called divide and conquer. The problem is divided into smaller copies of itself, the smaller copies are solved, and the answers are combined. Because each half is handled by the same method, the sort is written as a function that calls itself, which makes it the first recursive sort in this chapter.

Here's the sort, from `src/main.cpp`. The trace lines are left out of this listing:

```cpp
void mergeSort(std::vector<int>& values, std::size_t lo, std::size_t hi, long long& comparisons,
               std::ofstream* trace, bool& first) {
    if (hi - lo <= 1) {
        return;
    }
    std::size_t mid = lo + (hi - lo) / 2;
    mergeSort(values, lo, mid, comparisons, trace, first);
    mergeSort(values, mid, hi, comparisons, trace, first);
    merge(values, lo, mid, hi, comparisons, trace, first);
}
```

A run of one value is already sorted, so the function returns straight away. Otherwise it finds the middle, sorts the left half and the right half, and merges them. The function is called on the whole list with `lo` set to 0 and `hi` set to the length.

### The merge

Merging two sorted halves is simple. Keep one pointer at the front of each half. Compare the two front values, take the smaller, and move that pointer on. When one half runs out, copy the rest of the other half. The result is one sorted run.

```cpp
while (left < mid && right < hi) {
    comparisons++;
    if (values[left] <= values[right]) {
        merged.push_back(values[left]);
        left++;
    } else {
        merged.push_back(values[right]);
        right++;
    }
}
```

The merge uses `<=` rather than `<`. When two values are equal, the one from the left half goes first, so equal values keep their original order. That makes merge sort a stable sort, which matters when the values carry other data.

The merge uses a temporary list, `merged`, and copies the result back when it's done. That's the extra space the Big-O section counts.

### The data

The visualized list holds the values 1 through 20, each once, in a scrambled order:

```cpp
std::vector<int> small = {14, 3, 19, 7, 1, 12, 20, 5, 16, 9, 2, 17, 6, 11, 18, 4, 13, 8, 15, 10};
```

Press **Run**. The output is:

```
Visualized list: 20 values
Sorted: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
Comparisons: <count>
```

The timing list holds every whole number from -1,000 to 1,000, in a shuffled order. It's counted rather than drawn, and the output reports its head and tail after sorting:

```
Timing list: 2,001 values, from -1,000 to 1,000
First three after sorting: -1000 -999 -998
Last three after sorting: 998 999 1000
Comparisons: <count>
Sorted correctly: yes
```

The comparison counts depend on the order of the values, so the lesson reports them from the run. The one case you can predict exactly is an already sorted list, which the "Try" uses.

### Watch the sort

The program writes `trace.js` for the visualized list. Press **Run** first, then press **Visualize**. The visualizer shows the splitting and the merging:

* A split frame shows the part of the list being divided, with the rest faded out.
* Each comparison during a merge shows the two front values in amber, with the part being merged still bright.
* When a merge finishes, the merged part is shown in purple, and it's now in order.

The full sort is about 100 frames, so **Fast** or **Very fast** is the practical way to watch it through.

### Big-O analysis

Let n be the number of values.

**Levels.** Each split halves the size of the pieces, so the list is split until each piece holds one value. That takes about log₂n levels of splitting. The pieces at each level add up to all n values.

**Merge work.** Merging two runs takes at most one comparison for each value in them, so merging all the pieces at one level takes at most n comparisons. Over all the levels, that's at most n × log₂n comparisons. That's O(n log n).

---

**Best case.** Even for a list that's already in order, the splitting still happens at every level, so the sort still does O(n log n) work. The merge is cheaper on sorted input, since every value from the left half is taken first and the comparisons stop when the left half runs out. The count for sorted input is about half the number of values at each level, which is still O(n log n).

**Worst case.** The worst case has at most n log₂n comparisons, which is O(n log n).

**Average case.** For values in a random order, the average is also O(n log n).

**Space.** The merge needs a temporary list the size of the run being merged, so the extra space is O(n).

Merge sort is O(n log n) in every case, which is its main strength. Insertion sort is faster on a nearly sorted list, since its best case is O(n), but its worst case is O(n²). Merge sort never reaches O(n²), which makes it the safer choice for large lists where the order is unknown.

---

### Quiz

*These questions are written for this course.*

````quiz
Why does merge sort take about log₂n levels of splitting?
○ Because the list has to be split into exactly log₂n pieces.
→ Not quite. The number of pieces is not fixed in advance: the pieces keep halving until each holds one value.
◉ Because each split halves the size of the pieces, and halving n repeatedly reaches 1 after about log₂n steps.
→ Yes. That's the same halving that makes binary search O(log n).
○ Because the merge step has to be repeated log₂n times.
→ Not quite. The merge is done once for each split, and the number of splits follows from the halving.
````

````quiz
Why does merge sort use `<=` when comparing the front values of the two halves?
○ Because `<` would make the sort slower.
→ Not quite. The choice affects the order of equal values, not the speed.
◉ So that equal values keep their original order, which makes the sort stable.
→ Yes. The value from the left half is taken first when the two are equal.
○ So that the sort doesn't need a temporary list.
→ Not quite. The merge still needs a temporary list, whichever comparison is used.
````

---

### Try it in the runner

Change the visualized list to the values 1 through 20 in order, and predict the comparison count before you press **Run**. Each merge takes every value from the left half before the right half runs out, so the count is the number of left-half values at each merge. Adding those up over all the levels gives 40. Then press **Visualize** and watch how quickly the sorted pieces combine.

---

Merge sort gives O(n log n) in every case, at the cost of extra space for the merge. The next sort, quick sort, also aims for O(n log n), but it works in place and its worst case depends on the choice it makes at each split.
