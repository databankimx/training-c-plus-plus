## Summary: Modern features

This chapter covered two features from recent C++ standards that remove repetition and make missing results explicit.

* **`auto` takes the type from the initializer.** The type is still fixed at compile time, so it doesn't make C++ looser.
* **Structured bindings unpack a value into named parts.** A map's element becomes its key and value, and a pair becomes two variables.
* **`const auto&` in a loop avoids copies.** It also tells the reader that the loop doesn't change the container.
* **`std::optional` holds a value or nothing.** The return type shows that a result may be missing.
* **`std::nullopt` is the empty optional.** It replaces magic values such as -1.
* **Check an optional before using it.** Use `if`, `has_value`, or `value_or`. Dereferencing an empty optional is undefined behavior.

### Check your understanding

*These questions are written for this course.*

````quiz
Which statement about `auto` is true?
○ It lets a variable change type while the program runs.
→ Not quite. The type is fixed at compile time.
◉ It takes the type from the initializer, and the type never changes afterward.
→ Yes. auto saves writing the type, and keeps it fixed.
○ It can only be used with the built-in types.
→ Not quite. It works with class types as well.
````

````quiz
A function returns `std::optional<int>`. What must a caller do before using the value safely?
○ Nothing, since the value is always present.
→ Not quite. The function may return nothing, and the type says so.
◉ Check that the optional holds a value, or supply a fallback with value_or.
→ Yes. Reading an empty optional is undefined behavior.
○ Multiply it by zero first.
→ Not quite. That doesn't make an empty optional safe to read.
````

````quiz
Why is structured binding in a map loop clearer than `.first` and `.second`?
○ Because `.first` and `.second` are slower.
→ Not quite. Speed isn't the difference.
◉ Because the names describe the parts, such as name and score, instead of their positions.
→ Yes. Clear names make the loop easier to read and check.
○ Because structured bindings can change the map.
→ Not quite. A const binding reads the map without changing it.
````
