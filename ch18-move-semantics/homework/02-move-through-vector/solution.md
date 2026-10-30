## Solution: Move through a vector

`push_back(std::move(p))` moves the pointer into the vector. The vector now owns the resource, and `p` is empty, so the check prints `p owns nothing: yes`. The size is 1, since one element was added.

`std::move(holders[0])` takes the pointer out of the first element, and leaves that element empty. `back` now owns the resource. `pop_back` then removes the empty element. Destroying a null `unique_ptr` does nothing, so no release message prints at that point.

The resource is released once, when `back` goes out of scope at the end of `main`. That happens after `End`, which is why `Release vessel` is the last line.

For the first extension, the vector destroys its elements when it's cleared or destroyed, and the standard doesn't fix the order in which it does so. A program shouldn't depend on that order. Moving each element out before it's needed, as this exercise does, avoids the question.

For the second extension, a `unique_ptr` can't be copied, and `push_back` with an lvalue would have to copy it. The compiler refuses the copy, and the move is the explicit statement that the pointer is being handed to the vector.
