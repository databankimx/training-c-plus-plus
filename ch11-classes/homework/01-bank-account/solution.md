## Solution: Bank account

The balance is private, so `main` can change it only through `deposit` and `withdraw`. Each method checks its argument before it changes anything. The check comes first, so a rejected operation leaves the balance exactly as it was. That's the rule the output demonstrates: the last balance line matches the first.

The exception type follows the kind of problem. A bad amount passed in is an `invalid_argument`, since the caller supplied it. A withdrawal larger than the balance depends on the account's state, which is a runtime condition, so it's a `runtime_error`. Either choice could be defended, and the important part is that each message says what went wrong.

The constructor uses the same check as the deposit. A negative opening balance is refused for the same reason, and every object of the class follows the same rules from the first moment it exists.

`getBalance` is `const`, since it only reads. Declaring it that way lets the compiler confirm the promise, and lets the method be called on a `const` account if the program has one.

For the transfer extension, the risk is partial completion. If the withdrawal succeeds and the deposit throws, money has left one account without arriving in the other. A careful design checks the deposit's conditions before withdrawing, or undoes the withdrawal when the deposit fails.
