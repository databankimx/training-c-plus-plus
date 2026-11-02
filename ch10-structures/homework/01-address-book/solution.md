## Solution: Address book

The contacts are created with brace initialization, so each entry lists its name and phone in declaration order. The search is a `for` loop over the array, and each name is compared with the text the user typed.

The comparison ignores case, so `alan` finds `Alan`. The helper `lowercase` returns a lowercase copy of a string. It takes its argument by value, so the caller's text isn't changed. Both sides of the `==` are converted, so the comparison is between two lowercase strings. Converting only one side would fail for any name that has capitals in the stored data.

The cast to `unsigned char` before `std::tolower` is there because `std::tolower` requires a value that fits in an `unsigned char`. Passing a negative `char` value without the cast is undefined behavior. You'll see this pattern in any code that uses the `<cctype>` functions.

The `break` stops the loop at the first match. Without it, the loop would keep going, and a name that appeared twice would print twice. The `found` flag records whether anything matched, so the "No contact" message is printed only once, after the loop.

The array size of 3 appears in the declaration and in the loop condition. Changing the number of contacts means changing both, and forgetting one is a common bug. The first extension is the way to avoid it, by using a size that's computed from the array itself.
