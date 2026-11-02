## Unique pointers

The previous step worked with objects that live in a scope. Sometimes an object has to live longer than the scope that created it, or be created on the heap, in memory that lasts until it's deleted. Raw pointers can hold that memory, but a raw pointer doesn't say who is responsible for deleting the object. A forgotten `delete` leaks it, and a second `delete` crashes the program.

`std::unique_ptr` solves that. It's a class that holds one pointer, and it's the only owner of the object it points to. When the `unique_ptr` goes out of scope, it deletes the object, so the object's destructor runs and its resource is released. The RAII pattern from the last step, applied to heap memory.

Here's the core of the program, from `src/main.cpp`:

```cpp
{
    std::unique_ptr<Resource> owner = std::make_unique<Resource>("file C");
    owner->describe();
    std::cout << "Using file C\n";
}
```

`std::make_unique` creates the `Resource` on the heap and returns a `unique_ptr` that owns it. The header is `<memory>`. You never write `delete`, and you don't need to. The arrow `->` reaches a member through the pointer, the way `.` reaches it through a variable, so `owner->describe()` calls `describe` on the object the pointer owns.

Press **Run**. The output is:

```
Start
Acquire file C
Holding file C
Using file C
Release file C
After the block
```

The `Release` line comes at the closing brace. The `unique_ptr` goes out of scope there, deletes the `Resource`, and the destructor runs, just as it did when the object lived on the stack.

### One owner

A `unique_ptr` can't be copied. If you try to copy it, the compiler refuses, because two owners would both try to delete the same object. The owner can be moved to a new `unique_ptr`, which is the subject of the move semantics chapter. For now, the rule is simple: exactly one `unique_ptr` owns each object.

This is why the pointer says more than a raw pointer does. Reading the declaration `std::unique_ptr<Resource>`, you know that this variable is responsible for the object's lifetime. A raw `Resource*` tells you nothing about who deletes it.

### Checking for an object

A `unique_ptr` can be empty, which is useful when an object might not be created. Testing it in an `if` works the way the null-pointer check did in the pointers chapter. A default-constructed `unique_ptr` is empty, and using `->` on an empty one is undefined behavior, so check first.

---

### Quiz

*These questions are written for this course.*

````quiz
What happens when a `std::unique_ptr` goes out of scope?
○ It is copied to the outer scope.
→ Not quite. Ownership doesn't pass outward when a unique_ptr goes out of scope.
◉ It deletes the object it owns, which runs the object's destructor.
→ Yes. That's the RAII release, applied to heap memory.
○ It does nothing, and the object stays alive until the program ends.
→ Not quite. The unique_ptr releases its object when it goes out of scope.
````

````quiz
Why can't a `std::unique_ptr` be copied?
○ Because copying is too slow.
→ Not quite. The reason is correctness, not speed.
◉ Because two owners would both try to delete the same object.
→ Yes. Exactly one unique_ptr is responsible for each object.
○ Because pointers can never be copied in C++.
→ Not quite. Raw pointers can be copied. unique_ptr forbids it on purpose.
````

---

### Try it in the runner

Inside the block, add the line `std::unique_ptr<Resource> copy = owner;`, and predict what the compiler says before you press **Run**. The build fails, because copying a `unique_ptr` is forbidden. The error is the compiler enforcing single ownership.

Remove that line, and replace `owner->describe();` with `owner.get()->describe();`. `get` returns the raw pointer the unique_ptr holds, and the output doesn't change. The unique_ptr still owns the object, so the release still happens at the closing brace.

---

A `unique_ptr` gives heap memory a single owner, and its destructor releases the object automatically. The next step covers `std::shared_ptr`, which lets several owners share one object, and counts them.
