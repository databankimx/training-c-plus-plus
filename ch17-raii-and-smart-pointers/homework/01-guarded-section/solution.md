## Solution: Guarded section

The first call to `process` finishes normally. Its guard goes out of scope at the closing brace of `process`, so `Leave section` prints before the second call begins.

The second call throws after `Working`. The exception leaves `process` before its closing brace, but the guard is still destroyed on the way out. The destructor runs first, so `Leave section` appears before `Caught`. This is called stack unwinding: as the exception passes up through the functions, each object in the way is destroyed.

For the first extension, two guards in one function are destroyed in reverse order of creation. If the first guard is named `outer` and the second `inner`, the exception produces `Leave inner` and then `Leave outer`, before `Caught`.

For the second extension, an uncaught exception makes the program call `std::terminate`, which ends it. The C++ standard doesn't require the stack to be unwound before that happens. On most systems the guard's destructor does not run, which is why a `catch` is needed wherever a guard's cleanup matters.
