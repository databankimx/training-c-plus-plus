## Solution: Vowel tests

The function walks the characters of the word, and adds one for each lowercase vowel. The condition chains the five letters with `||`, so any one of them is enough. The empty string has no characters, so the loop never runs and the function returns 0, which is why that check is worth having.

The four checks cover a word with some vowels, the empty word, a word with none, and a longer word with several. "rhythm" is a useful check because it has no vowels at all, and a function that accidentally counted `y` would fail it.

For the first extension, "HELLO" has no lowercase vowels, so the function returns 0. Whether that's right depends on the specification. If uppercase vowels should count, the function is wrong, and the check reveals the gap. If the specification says only lowercase letters count, the check should expect 0. Deciding the expected answer is part of writing the test.

For the second extension, a check you write yourself should have its answer worked out by hand before the program runs. A check whose answer came from running the program would only confirm that the program agrees with itself, which proves nothing.
