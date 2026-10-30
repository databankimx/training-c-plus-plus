## Solution: Ownership handoff

The `consume` function takes its `unique_ptr` by value, so the caller's pointer is moved into the function's parameter. From that moment, the function is the only owner. When it returns, the parameter goes out of scope, the `unique_ptr` deletes the resource, and `Release handoff` prints. That happens before `main` continues, which is why `Back in main` comes after it.

For the first extension, a `const std::unique_ptr<Resource>&` parameter is a reference. Nothing is moved, and `main` remains the owner. The release does not happen inside `consume`. It happens at the end of `main`, after `End`. The function can use the resource, but it isn't responsible for its lifetime.

For the second extension, a `unique_ptr` can't be copied. Without the move, the argument would have to be copied into the by-value parameter, and the compiler refuses that. The move is the explicit statement that ownership is being transferred, so the compiler accepts it.
