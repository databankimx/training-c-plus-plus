## Solution: Unit converter

The example reads the temperature into a `double`, so `100.5` works as well as `100`. The formula is written as `celsius * 9.0 / 5.0 + 32.0`, with decimal constants throughout. That's the detail the lesson warned about: with `9 / 5` as whole numbers, C++ would divide first and give `1`, and every answer would be wrong.

The result is stored in a `const` variable. Nothing changes it after the calculation, so the compiler is allowed to protect it, and a reader knows at a glance that it's fixed.

The prompt uses `std::flush`, as in the lesson, so the question appears before the program waits for input.
