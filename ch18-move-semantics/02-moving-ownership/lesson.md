## Moving ownership

The previous step moved an object's contents. Some types can't be copied at all, because a copy would be wrong. A `std::unique_ptr` owns one object, and two owners would delete it twice. Such a type is called move-only, and the move is the only way to hand the object to someone else.

This step uses a `unique_ptr` from the smart pointers chapter, so the ownership rule is already familiar. The only new part is the transfer.

Here's the transfer, from `src/main.cpp`:

```cpp
std::unique_ptr<Resource> a = std::make_unique<Resource>("file E");
std::unique_ptr<Resource> b = std::move(a);
```

After the second line, `b` owns the resource, and `a` owns nothing. The move constructor of `unique_ptr` takes the pointer from `a` and leaves `a` holding null. That's the moved-from state in its most useful form: an empty pointer, which you can test with `if`, rather than an object with unspecified contents.

Press **Run**. The output is:

```
Start
Acquire file E
a owns nothing: yes
b owns the resource: yes
End
Release file E
```

The resource is acquired once, and it's released once, when `b` goes out of scope at the end of `main`. `a` releases nothing, because it doesn't own anything. Since the transfer happened before any work was done with the object, there's only one owner at each moment.

### Moves and functions

The same transfer lets you pass ownership into a function. A function that takes a `unique_ptr` by value, and is called with `std::move`, becomes the owner for the duration of the call. When the function returns, the object is released, unless the function has passed it on. This is how a program hands work to another part of the code while making clear who is responsible at each step.

### When to move

Move when the source is no longer needed, and when you want the object to live somewhere else. Copying is the right choice when both objects need their own value. A move is a promise that the source won't be read for its old contents afterward.

---

### Quiz

*These questions are written for this course.*

````quiz
After `std::unique_ptr<Resource> b = std::move(a);`, what does `a` hold?
○ The same resource as b, so both can use it.
→ Not quite. A unique_ptr can't share ownership, so a no longer holds the object.
◉ Nothing. It's empty, and b owns the resource.
→ Yes. The move transfers the pointer and leaves the source null.
○ A copy of the resource.
→ Not quite. A unique_ptr can't be copied, so no second object exists.
````

````quiz
Why does `std::unique_ptr` forbid copying but allow moving?
○ Because moving is faster than copying.
→ Not quite. Speed isn't the reason for the rule.
◉ Because a move leaves exactly one owner, while a copy would make two owners of the same object.
→ Yes. Moving keeps the single-owner rule true at every moment.
○ Because the compiler can't generate a copy for pointers.
→ Not quite. The compiler could copy a pointer, but the copy would break the ownership rule.
````

---

### Try it in the runner

Replace the move with `std::unique_ptr<Resource> c = a;` and press **Run**. The build fails, because copying a `unique_ptr` is forbidden. Restore the move before you continue.

Then add a line that calls `a->` on the empty `a`, and predict what happens. It's undefined behavior: an empty unique_ptr has no object to reach, and the program may crash. That's why the `if` test on `a` is the safe way to check.

---

A move transfers ownership or contents from one object to another, and the source must be left valid. Moving is most useful with types that can't be copied, such as `unique_ptr`. The chapter summary follows, and then two homework exercises that use moves with ownership.
