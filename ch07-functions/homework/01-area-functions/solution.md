## Solution: Area functions

Each function does one job and returns its result, so `main` decides what to do with it. `rectangleArea` multiplies its two parameters. `circleArea` uses the radius twice in the formula, and returns the product with pi.

The parameters are `double` because the inputs may have decimals, such as a width of 2.5. Returning a `double` means the caller gets the full value, and the two decimal places are applied only when `main` prints.

The pi value is stored in a `const` variable inside `circleArea`, so the number is named and can't be changed by accident. A later chapter covers placing constants where several functions can share them.

The zero case works without any special handling, since multiplying by zero gives zero. That's the reason to test it: it confirms the formula doesn't need a guard that isn't there.
