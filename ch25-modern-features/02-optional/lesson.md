## std::optional

Many functions can't always produce a result. A search might find nothing, a parse might fail, and a lookup might have no entry. Older code often returned a magic value, such as -1, to mean "no answer". That works only until a valid result happens to match the magic value, and the caller can forget to check for it.

`std::optional` makes the possibility of no answer part of the return type. An `std::optional<int>` holds either an `int` or nothing, and the type itself says so.

### Returning nothing

The function from `src/main.cpp` returns an index when it finds the target, and `std::nullopt` when it doesn't:

```cpp
std::optional<int> findIndex(const std::vector<int>& values, int target) {
    for (int i = 0; i < static_cast<int>(values.size()); i++) {
        if (values[static_cast<std::size_t>(i)] == target) {
            return i;
        }
    }
    return std::nullopt;
}
```

`return i` converts the `int` into an optional that holds it. `std::nullopt` is the optional that holds nothing. The return type makes the difference visible to anyone who calls the function.

### Checking and using the result

The caller has two safe ways to read an optional. The first checks it, then reads the value with `*`:

```cpp
std::optional<int> found = findIndex(values, 8);
if (found) {
    std::cout << "Found at " << *found << "\n";
}
```

The second supplies a fallback with `value_or`:

```cpp
std::cout << missing.value_or(-1) << "\n";
```

Press **Run**. The output is:

```
Found at 1
Not found
-1
```

The optional for 8 holds the index 1, so `if (found)` is true, and `*found` gives 1. The optional for 99 holds nothing, so the check reports "Not found", and `value_or(-1)` gives the fallback.

### Reading an empty optional

`*` on an empty optional is undefined behavior, just as dereferencing a null pointer is. The check with `if` or `has_value()` comes first, or `value_or` supplies the fallback. The `value()` member throws an exception instead, which is safer when a missing value is truly unexpected.

---

### Quiz

*These questions are written for this course.*

````quiz
What does `std::nullopt` represent?
○ The number zero.
→ Not quite. It isn't a number, and it doesn't stand for zero.
◉ An optional that holds no value.
→ Yes. It says the function has no answer, without using a magic number.
○ An error code the caller must look up.
→ Not quite. It's a value of the optional type, and the caller tests for it directly.
````

````quiz
Why is `std::optional<int>` better than returning -1 to mean "not found"?
○ Because -1 is slower to compare.
→ Not quite. Speed isn't the reason.
◉ Because the type makes the missing case visible, and a valid index can never be confused with it.
→ Yes. The caller can't mistake the empty case for a real result.
○ Because -1 can't be stored in an int.
→ Not quite. It can, which is why it's a risk.
````

---

### Try it in the runner

Call `findIndex(values, 4)` and print it with `value_or(-1)`. Predict the output before you press **Run**. The value 4 is at index 0, so the output is 0. Index 0 is a valid answer, which is exactly why a magic value of 0 for "not found" would be a mistake.

---

`std::optional` puts the possibility of no answer in the type, so the compiler and the reader both see it. The next step is the chapter summary, and then two homework exercises that use structured bindings and optional.
