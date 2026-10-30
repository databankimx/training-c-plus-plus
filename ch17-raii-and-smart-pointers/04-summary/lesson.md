## Summary: RAII and smart pointers

This chapter covered how C++ ties the release of a resource to the lifetime of an object, and how smart pointers apply the same idea to heap memory.

* **RAII ties a resource to an object.** The constructor acquires the resource, and the destructor releases it.
* **Destructors run at the end of scope.** A local object is destroyed when its block, function, or program ends, including on an early return or a throw.
* **Objects are destroyed in reverse order of creation.** The last one created is released first.
* **`std::unique_ptr` has one owner.** It deletes the object when it goes out of scope, and it can't be copied.
* **`std::make_unique` creates the object and its owner together.** No `new` or `delete` is needed.
* **`std::shared_ptr` shares ownership.** Each copy adds an owner, and the object is released when the last owner is gone.
* **`use_count` reports the owners.** It's useful for learning, but it isn't a safe basis for logic in threaded code.
* **Cycles leak shared objects.** Two shared pointers that own each other keep both alive forever.

### Check your understanding

*These questions are written for this course.*

````quiz
What runs when a local object goes out of scope?
○ Its constructor, to clean it up.
→ Not quite. The constructor runs when an object is created, not when it ends.
◉ Its destructor, which releases the resource the object holds.
→ Yes. That's the RAII pattern.
○ Nothing, since local objects are cleaned up by the operating system.
→ Not quite. The destructor runs at the end of the scope.
````

````quiz
Why does `std::unique_ptr` forbid copying?
○ Because copying is slower than moving.
→ Not quite. The reason is ownership, not speed.
◉ So that exactly one owner deletes the object.
→ Yes. Two owners would delete the same object twice.
○ Because the pointed-to object is too large to copy.
→ Not quite. The object's size has nothing to do with the rule.
````

````quiz
Three shared pointers own one object, and one of them is reset. What happens?
○ The object is released immediately.
→ Not quite. Two owners remain, so the object is still alive.
◉ The owner count drops to two, and the object stays alive.
→ Yes. The object is released only when the last owner goes away.
○ The other two owners are deleted as well.
→ Not quite. Resetting one owner doesn't affect the others.
````
