## Solution: Counter

The constructor takes a starting value with a default of zero: `Counter(int start = 0)`. A default argument lets one constructor serve both purposes. `Counter c;` calls it with no argument, so the start is zero, and `Counter d(10);` passes 10. That answers the second extension directly: two constructors aren't needed when one can take a default.

The member `count` has its own default of zero, and the constructor assigns the starting value over it. Either way, the counter always has a value, so no object is ever created in an unknown state.

`value` is `const`, since it only reads. `increment` and `reset` change the count, so they aren't `const`.

The output's three lines test three different paths: three increments, a reset, and a counter that starts somewhere other than zero. If any of them is wrong, the line that disagrees shows which path has the fault.
