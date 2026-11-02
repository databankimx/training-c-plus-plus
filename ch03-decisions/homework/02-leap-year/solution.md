## Solution: Leap year

The example stores the result in a `bool` called `leap`, so the rule is written once and then used in one `if`.

The rule is split into the two parts from the lesson. The first part, `year % 4 == 0`, must be true for any leap year. The second part, in parentheses, handles the century exception. It's true when the year isn't divisible by 100, or when it's divisible by 400. The `||` lets either case count.

The two parts are joined with `&&`. The `%` operator runs before `==` and `!=`, as the precedence rules say, so `year % 4 == 0` is worked out as `(year % 4) == 0` without any parentheses needed. Parentheses around the second part are there for the reader, since they show that the `||` belongs with the century check.

The years to check are 1900, which fails the century test, and 2000, which passes it. If your program says 1900 is a leap year, the century part is missing or wrong.
