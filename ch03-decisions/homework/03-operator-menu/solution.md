## Solution: Operator menu

The example reads the operator as a `char`, then reads the two numbers as `double` values, so decimal inputs such as `2.5` work. The `switch` compares the operator with each case label, and each case ends with `break`.

The division case is the only one with an `if`. Dividing by zero is checked before the division happens, so the program never tries it. For `double` values, C++ wouldn't stop the division, and the result would be infinity, which isn't what a calculator should print.

The `default` case covers every other character, including `%`. Because the operator is read as a single character, an input such as `++` would read only the first `+` and leave the second one in the input. The program doesn't handle that, and a later chapter that covers reading whole lines would.

The `%` extension is a good test of understanding. The `%` operator works only on integers, as the arithmetic lesson explained, so the `%` case needs `int` values, or a different approach for decimals.
