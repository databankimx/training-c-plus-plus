## auto and structured bindings

Modern C++ removes much of the repetition that older code needed. Two features do most of that work: `auto`, which lets the compiler work out a variable's type from the value it's given, and structured bindings, which unpack a value that holds several parts into separate named variables.

### auto

The type of a variable is usually obvious from its initializer, and writing it out again adds length without information. `auto` says the type is taken from the value:

```cpp
auto count = 3;        // int
auto average = 4.5;    // double
```

`auto` doesn't make C++ loose about types. The variable still has exactly one type, decided at compile time, and the compiler reports an error for any later use that doesn't fit it. The types of long iterators and long template names are where `auto` helps most, since writing them out is tedious and error-prone.

### Structured bindings

A `std::map` element holds a key and a value. Before C++17, the loop had to name the pieces through `.first` and `.second`. A structured binding names them directly:

```cpp
for (const auto& [name, score] : scores) {
    std::cout << name << ": " << score << "\n";
}
```

Each element of the map is a pair, and `[name, score]` gives its two parts names. The `const auto&` form avoids copying each element, and `const` keeps the map unchanged.

Press **Run**. The output is:

```
Ada: 91
Grace: 88
3 4.5
```

The map keeps its keys in sorted order, so Ada comes before Grace. The last line comes from the pair, unpacked the same way.

### Where bindings help

A structured binding works with any type that the standard library can unpack: pairs, tuples, arrays of fixed size, and types a class declares for the purpose. It names parts that already exist, so it doesn't copy the value unless the binding is declared without `&` or `const&`. Use it when the parts have clear names, as the key and value of a map do, and use `.first` and `.second` or a plain variable when the names would be unclear.

---

### Quiz

*These questions are written for this course.*

````quiz
What does `auto count = 3;` give `count`?
○ The type int, because the program has no other choice.
→ Not quite. It's int here, but the reason is the initializer, not a default.
◉ The type int, taken from the value 3, and fixed at compile time.
→ Yes. auto takes the type from the initializer, and the type never changes after that.
○ A type that can change while the program runs.
→ Not quite. A variable declared with auto still has one fixed type.
````

````quiz
Why is `for (const auto& [name, score] : scores)` written with `&`?
○ Because the map can't be read without it.
→ Not quite. The map can be read without a reference.
◉ So each element is referred to rather than copied, and const keeps the map unchanged.
→ Yes. The reference avoids a copy, and const documents that the loop only reads.
○ Because structured bindings must always be references.
→ Not quite. A binding can be a copy, but the reference is the usual choice for a loop like this.
````

---

### Try it in the runner

Add `{"Linus", 95}` to the map, and predict the order the loop prints the names in before you press **Run**. Map keys are sorted, so the output is Ada, Grace, and then Linus, with Linus's score on the last line of the loop.

---

`auto` and structured bindings cut the noise from code that already works, without changing what it does. The next step is `std::optional`, which lets a function say that it has no answer, without a magic value.
