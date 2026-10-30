## Summary: Move semantics

This chapter covered moving, the alternative to copying, and how it applies to ownership.

* **A copy makes an independent object.** The copy constructor takes a `const` reference and duplicates the contents.
* **A move takes the contents from another object.** The move constructor takes an rvalue reference, and the source is left valid but unspecified.
* **`std::move` permits a move.** It turns its argument into an rvalue. It doesn't move anything itself.
* **A moved-from object is valid, but its value is not to be relied on.** Assign to it or let it be destroyed. Don't read its old contents.
* **Move-only types can't be copied.** `std::unique_ptr` is the common example, and moving is the only way to transfer it.
* **A moved-from `unique_ptr` is empty.** Test it with `if` before using it.
* **Move when the source is finished with.** Copy when both objects need their own value.

### Check your understanding

*These questions are written for this course.*

````quiz
What does an rvalue reference, written `Buffer&&`, allow?
○ It allows the object to be copied more quickly.
→ Not quite. The speed comes from taking the contents, not from the reference itself.
◉ It allows a constructor to take the contents of an object that is about to be discarded.
→ Yes. That's what the move constructor uses.
○ It allows the object to be used by two threads at once.
→ Not quite. Rvalue references have nothing to do with threads.
````

````quiz
What is the safe way to use a moved-from `std::string`?
○ Print its contents to check that the move worked.
→ Not quite. Its contents are unspecified after a move, so reading them is a bug.
◉ Assign it a new value, or let it be destroyed.
→ Yes. Those are the valid uses of a moved-from object.
○ Copy it, and trust the copy to contain the original text.
→ Not quite. The original text was moved away.
````

````quiz
Why can a program move a `std::unique_ptr` but not copy it?
○ Because moves are cheaper than copies.
→ Not quite. The reason is ownership, not cost.
◉ Because a move leaves one owner, while a copy would leave two owners of one object.
→ Yes. Single ownership is the rule that a unique_ptr exists to enforce.
○ Because unique_ptr has no members to copy.
→ Not quite. It holds a pointer, which is exactly what would be copied.
````
