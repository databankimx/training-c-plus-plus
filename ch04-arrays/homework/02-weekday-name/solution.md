## Solution: Weekday name

The example declares the names as an array without a size, so the compiler counts the seven values. The user's number is checked against the valid range before the array is read. The check is `number < 1 || number > 7`, which uses `||` so that either bad case triggers the message.

The lookup subtracts 1, because day 1 is at index 0. Had the program used the number directly, day 1 would print Tuesday, and day 7 would read past the end of the array.

Returning early after the invalid message keeps the rest of the program from running with a value it can't use. In a longer program, the same idea applies to any check that fails: deal with it, then stop.

The number 7 appears twice. A better version uses `std::size(days)` in both places, so the check stays correct if the array changes. That's the first extension in the exercise.
