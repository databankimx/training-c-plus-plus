## Solution: Debug option

The option is declared with `option`, and it's off by default. The `if(SHOW_STEPS)` block runs only when it's on, and then it defines `SHOW_STEPS_ON` for the program target. Because the definition is `PRIVATE` to the program, only the program's own code sees it.

The loop adds each number to `total`. The `#ifdef SHOW_STEPS_ON` block prints one line after each addition, and it's left out of the compiled program when the option is off. With the option off, the output is just `Sum: 10`.

For the first extension, the option belongs in `CMakeLists.txt` because it's a property of the build, not of the code. The same source file can then be built both ways. Without the definition, `#ifdef SHOW_STEPS_ON` is false, the step lines are skipped silently, and nothing reports the missing definition. A typo in the name of the symbol causes exactly that kind of quiet failure, which is why the name should be checked against the option.

For the second extension, two options can be on at the same time. The code has to decide what that means, for example by printing both calculations, or by refusing the combination with an `#error` directive, which stops the build with a message if the two definitions are both present.
