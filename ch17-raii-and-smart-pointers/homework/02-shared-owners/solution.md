## Solution: Shared owners

`std::make_shared` creates the resource and the first owner, `original`. The first `push_back` copies the shared pointer into `holders`, which adds an owner, so the count is 2. The second `push_back` adds a third owner, so the count is 3.

`holders.clear()` destroys the two copies inside the vector, which removes their ownership. Only `original` is left, so the count is 1. The resource is still alive, and `End` prints before anything is released.

`Release shared` comes after `End` because `original` is the last owner, and it's destroyed when `main` returns. Its scope is the whole function, so the release happens at the very end.

If `original.reset()` were called before `clear()`, the `original` owner would go first. The count would then be 2, then 1, and `clear()` would remove the last owner. The resource would be released at the `clear()` call, before `End` is printed.

For the extension, a second resource with its own shared pointer has its own control count, so its owner count is independent of the first. For threads, another thread can change the count between the moment you read it and the moment you act on it, so the value may be stale by the time it's used.
