## Insertion sort

Insertion sort works the way many people sort a hand of playing cards. Pick up one card at a time, and slide it left until it sits in the right place among the cards already in your hand. The cards you've already placed are always in order, so each new card needs only a short walk into place.

Here's the sort, from `src/main.cpp`. The trace lines are left out of this listing, as they were for the other sorts:

```cpp
void insertionSort(std::vector<int>& values, long long& comparisons, long long& moves, std::ofstream* trace,
                   bool& first) {
    std::size_t n = values.size();
    for (std::size_t i = 1; i < n; i++) {
        std::size_t j = i;
        while (j > 0) {
            comparisons++;
            if (values[j - 1] > values[j]) {
                int temp = values[j - 1];
                values[j - 1] = values[j];
                values[j] = temp;
                moves++;
                j--;
            } else {
                break;
            }
        }
    }
}
```

The outer loop takes the value at index `i` and treats it as the card to place. The inner loop compares it with the value before it. If that value is larger, the two swap, so the card moves one place left, and the loop looks again. If the value before it isn't larger, the card has reached its place, and the loop stops. The values before index `i` are always in order, which is why the inner loop can stop as soon as it finds a smaller value.

The swap is written out in full, so the array always holds the same values, just in a different order. That keeps the visualizer honest: every frame shows a real arrangement of the list.

### The data

The visualized list holds the values 1 through 20, each once, in the same scrambled order as the selection sort:

```cpp
std::vector<int> small = {14, 3, 19, 7, 1, 12, 20, 5, 16, 9, 2, 17, 6, 11, 18, 4, 13, 8, 15, 10};
```

Press **Run**. The output is:

```
Visualized list: 20 values
Sorted: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
Comparisons: 108, moves: 91
```

The timing list holds every whole number from -1,000 to 1,000, in a shuffled order. It's counted rather than drawn, and the output reports its head and tail after sorting:

```
Timing list: 2,001 values, from -1,000 to 1,000
First three after sorting: -1000 -999 -998
Last three after sorting: 998 999 1000
Comparisons: <count>, moves: <count>
Sorted correctly: yes
```

The counts for the timing list depend on the shuffle, so the lesson reports them from the run. For the visualized list, the moves equal the number of pairs that start out of order. Each move fixes exactly one such pair, and that's why the count is 91.

### Watch the sort

The program writes `trace.js` for the visualized list. Press **Run** first, then press **Visualize**. Each comparison is a frame, with the two neighbors being compared shown in amber. When a move happens, a second frame shows the swapped pair in purple. The left part of the list, which is already sorted, is shown in green, and it grows as each card is placed.

**Fast** or **Very fast** is the practical way to watch the whole sort.

### Big-O analysis

Let n be the number of values.

**Comparisons.** Each new value is compared with the values before it, until it finds a value that isn't larger. The number of comparisons for one value is one more than the number of moves it makes, except when it moves all the way to the front, where the loop ends without a comparison. That gives the total in the worst case: the values are in reverse order, so each new value moves all the way to the front. The moves then are 0 + 1 + 2 + ... + (n - 1), which is n(n - 1) / 2. That's O(n²).

---

**Best case.** If the list is already in order, each new value is compared once with the value before it, finds that it isn't larger, and stops. That's n - 1 comparisons and no moves, which is O(n).

**Average case.** For values in a random order, each new value moves about halfway into the sorted part, so the average is about n(n - 1) / 4 moves and comparisons. That's O(n²).

**Space.** The sort works on the list itself and keeps only a few indexes, so its extra space is O(1).

Insertion sort adapts to its input. A nearly sorted list has few moves, so it finishes quickly. Selection sort doesn't adapt in this way: its comparisons are n(n - 1) / 2 whatever the order. That's the main difference between the two, and it's why insertion sort is often the best choice for small lists or lists that are nearly in order.

---

### Quiz

*These questions are written for this course.*

````quiz
What is the best-case cost of insertion sort on a list of n values?
○ O(n²), the same as the worst case.
→ Not quite. Insertion sort adapts to its input, so a sorted list is much cheaper.
◉ O(n), since each value is compared once and stops at once.
→ Yes. A sorted list needs n - 1 comparisons and no moves.
○ O(log n), since the sorted part is searched by halving.
→ Not quite. Insertion sort walks through the sorted part, one place at a time.
````

````quiz
Why does insertion sort make 91 moves on the visualized list?
○ Because there are 20 values and 91 is more than 20.
→ Not quite. The count depends on the order of the values, not just on their number.
◉ Because each move fixes one pair that starts out of order, and there are 91 such pairs.
→ Yes. The moves equal the number of inversions, which is the count of out-of-order pairs.
○ Because the sort moves every value to the front.
→ Not quite. Most values stop before they reach the front.
````

---

### Try it in the runner

Change the visualized list to the values 20 down to 1, in reverse order. Predict the comparison count before you press **Run**. Every value moves all the way to the front, so the answer is 190, which is 20 times 19 divided by 2. Then press **Visualize** and watch each value slide left.

---

Insertion sort is the simplest sort that adapts to its input, and it's the sort most real libraries use for small pieces of a larger job. The next sorts, merge sort and quick sort, aim for O(n log n) on large lists.
