## Vectors

Arrays have a fixed size. Once you've declared `int nums[3]`, it holds three values, and that's the end of it. Most real programs don't know how many values they'll need until they run, so the standard library provides `std::vector`, a container that grows as you add to it.

Here's the program for this step, in `src/main.cpp`. It starts with an empty vector and adds three scores:

```cpp
std::vector<int> scores;
scores.push_back(72);
scores.push_back(88);
scores.push_back(95);
```

`push_back` adds a value to the end. The vector makes room for it, so you never state a size. The header is `<vector>`, and the type is written as `std::vector<int>`, where the angle brackets name the type of each element.

Press **Run**. The output is:

```
Count: 3
First: 72
Last: 95
Total: 255
Average: 85
After adding: 4
Index 10 is out of range.
```

### Reading the elements

A vector takes an index in square brackets, just as an array does, and index 0 is the first element. `scores.size()` gives the number of elements, and `scores.at(i)` gives the element at index `i`. The two differ in what happens when the index is out of range. `scores[10]` doesn't check, and reading past the end is undefined, as it was for arrays. `scores.at(10)` checks the index, and throws a `std::out_of_range` exception, which the program catches.

Use `at` while you're learning, and when an index comes from outside the program, such as user input. Use `[]` only when you've checked the index yourself, or when the loop guarantees it.

### Looping over a vector

The range-based `for` works on a vector just as it does on an array:

```cpp
for (int score : scores) {
    total += score;
}
```

Each element is copied into `score` in turn, and the body runs once per element. The loop doesn't need `size()`, so it can't run past the end.

### Adding and growing

The vector grows each time you call `push_back`. The program adds a fourth score after the loop, and `size()` reports 4. That growth is the reason vectors exist: the size is decided while the program runs, from the data it reads.

### More vector methods

The program's last part uses the methods students will reach for next. Each one is a member function, called with a dot, as the methods chapter described.

```cpp
std::vector<int> stack = {1, 2, 3};
stack.pop_back();
stack.insert(stack.begin() + 1, 99);
stack.erase(stack.begin());
```

`pop_back` removes the last element, which pairs with `push_back` to make a stack. `front` and `back` read the first and last elements, and `empty` tells you whether there are any. The printed lines are `Front: 1, back: 3`, then `After pop_back: size 2, back 2`, and then `Elements: 99 2`.

`insert` and `erase` take a position rather than an index, and the position is written `stack.begin() + 1`. Iterators, which `begin` returns, are covered later in the course, so for now read `begin() + 1` as "the second element". Inserting before that position puts 99 in the middle, and every element after it moves one place along. `erase` removes the element at a position and closes the gap. Both take time in proportion to how many elements move, which is the cost point from the section below.

`clear` removes every element, and `reserve` makes room for elements without adding any. The program checks `capacity`, which reports the space the vector has allocated. A reserved vector has capacity without size, which is the difference the cost section described.

### Quick reference

| Method | What it does | Typical cost |
|---|---|---|
| `push_back(x)` | Adds `x` after the last element | Constant on average |
| `pop_back()` | Removes the last element | Constant |
| `front()`, `back()` | Reads the first or last element | Constant |
| `at(i)`, `[i]` | Reads the element at index `i` | Constant |
| `size()`, `empty()` | Counts the elements, or tests for none | Constant |
| `capacity()` | Reports the allocated space | Constant |
| `reserve(n)` | Makes room for `n` elements | Linear when it has to copy |
| `clear()` | Removes every element, keeping the capacity | Linear in the number of elements |
| `insert(pos, x)` | Inserts `x` before position `pos` | Linear, since later elements move |
| `erase(pos)` | Removes the element at `pos` | Linear, since later elements move |

The costs are the typical ones for a vector, and they are what the efficiency chapter measures. Only `push_back` is described as constant on average, since an occasional growth copies the whole block.

### What a vector costs

A vector keeps its elements side by side in one block of memory. That layout is the reason it's fast to read: neighboring elements are usually already in the processor's cache when the program reaches them, so a loop over a vector runs quickly, and indexing into it is a single calculation.

Growing costs more, and the cost is worth understanding. When the block is full, the vector allocates a larger block and copies every element across. That copy is expensive, but it happens rarely, because the block grows by a fixed multiple each time, not by one element. Over many `push_back` calls, the cost of the copies is spread across the additions, so each addition is cheap on average. That's why adding to the end of a vector is described as constant time on average, a claim the efficiency chapter tests with operation counts.

Two habits help. If you know roughly how many elements you'll need, call `reserve` first, so the vector allocates once. And remember that a vector can hold more space than it uses, so its memory footprint can be larger than its size suggests.

---

### Quiz

*These questions are written for this course.*

````quiz
Which member function adds a value to the end of a vector?
○ add
→ Not quite. Vectors use push_back to add at the end.
◉ push_back
→ Yes. push_back adds one element after the last one, and the vector grows to fit.
○ append
→ Not quite. That name isn't a vector member.
````

````quiz
What is the difference between `scores[10]` and `scores.at(10)` when the vector has four elements?
○ Both throw an exception.
→ Not quite. The [] form doesn't check, and only at throws.
◉ at checks the index and throws std::out_of_range, while [] reads past the end with undefined results.
→ Yes. The checked form is safer for indexes that come from outside the program.
○ Neither is allowed on a vector.
→ Not quite. Both are valid; they differ in checking.
````

````quiz
A vector holds 1000 elements. What happens to the elements after position 10 when you call `insert` at position 10?
○ Nothing. Only the new element is written.
→ Not quite. The elements after the position have to make room for the new one.
◉ Each of them moves one place along, so the work grows with the number of elements after the position.
→ Yes. That's the linear cost in the quick reference table.
○ They are all copied into a new vector.
→ Not quite. Only the elements after the position move, and the vector keeps its block.
````

---

### Try it in the runner

Change `at(10)` to `scores[10]`, and press **Run**. The program still builds, since the compiler doesn't check the index, and reading past the end is undefined. The output might look the same, or the program might crash. Predict which, and change it back, since `at` makes the failure visible.

Then add `scores.size()` to the range-based loop's condition, by writing `for (int i = 0; i < scores.size(); i++)` with `scores[i]` in the body. The compiler may warn about comparing an `int` with the size, which is an unsigned type. Replace `int` with `std::size_t` for the index, and check that the warning disappears.

---

A vector is an array that grows, with a checked way to read elements and a range-based loop that visits them. The next step stores values under keys rather than positions, which is the job of `std::map`.
