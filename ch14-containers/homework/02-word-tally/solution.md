## Solution: Word tally

The first loop counts the words, using `counts[word]++`. As the maps lesson showed, `[]` creates each word the first time it's seen, so the count starts at one.

The printing loop visits the entries in key order, so `blue` comes before `green` and `red`. That order is guaranteed by the map, which is why the printed output is the same every time. An unordered map would not give that guarantee, and the extension about unordered maps is a good place to see why.

The most common word is found in a second pass over the map. `bestCount` starts at zero, so the first entry always becomes the best so far. Each later entry replaces it only when its count is strictly greater, so a tie keeps the earlier word. The extension asks you to report every tie, which needs a different approach.

The counts are compared, not the positions, so `red` wins with three occurrences, whichever order the words were listed in.
