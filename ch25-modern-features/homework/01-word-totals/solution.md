## Solution: Word totals

The map keeps its keys in sorted order, so the first loop prints apple, fig, and pear, whatever order they were inserted in. Each element is a key and value pair, and the structured binding `[word, count]` names the two parts, so the body reads as "print the word and its count".

The second loop doesn't use `word`. That's allowed: a structured binding can name parts the loop doesn't need, and the compiler doesn't require every name to be used. The total is 3 + 2 + 5, which is 10.

For the first extension, a second map is searched with `count(word)` or `find(word)`, which both work on the key alone. Checking membership with `count` is the shortest form, since a map holds each key at most once.

For the second extension, `auto [word, count]` copies each key and value. For a `std::string` key, that copies the text on every pass. `const auto&` refers to the element instead, so the loop does no copying, and `const` promises the loop won't change the map.
