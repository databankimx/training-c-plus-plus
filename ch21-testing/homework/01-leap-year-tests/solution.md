## Solution: Leap-year tests

The function checks the rule in the order that makes it simple. A year divisible by 400 is always a leap year, so that's tested first. A year divisible by 100 but not 400 is not a leap year, so that's tested next. Anything else is a leap year exactly when it's divisible by 4. Testing 400 before 100 is what makes 2000 a leap year and 1900 not one.

The four checks cover the four kinds of year the rule distinguishes: an ordinary leap year (2024), a century that isn't a leap year (1900), a century that is (2000), and an ordinary year (2023). Each check is named after the claim it tests, so a failure names the case that went wrong.

The `!` in front of `isLeapYear(1900)` negates the result, so that check reads "1900 is not a leap year" and passes when the function returns false.

For the first extension, 1600 is a multiple of 400, so it's a leap year, and 2028 is a multiple of 4 that isn't a multiple of 100, so it's the ordinary leap-year case. Between them, the four original checks and these two cover every branch of the function.

For the second extension, changing the function to get 1900 wrong would fail the check for 1900, and possibly not the others. The edge cases are the ones that show it, because the other years don't reach the branch that treats centuries specially.
