## Solution: Sort by length

The lambda takes two strings by `const` reference, so the comparison doesn't copy them. It returns true when `a` is shorter than `b`, which puts the shortest words first.

`std::stable_sort` is the key choice. The lengths of "pear" and "kiwi" are equal, so the comparison says neither comes before the other. A stable sort keeps equal values in their original order, and "pear" was first in the list, so it stays first. The output is `By length: fig pear kiwi banana`.

With `std::sort`, equal values may come out in either order. Some runs of that sort would print `kiwi pear`, and no run is guaranteed to keep the input order. That's why the exercise asks you to try it.

For the first extension, the alphabetical tie-break would be `a.size() < b.size() || (a.size() == b.size() && a < b)`. With that rule, "kiwi" comes before "pear", and `std::sort` gives the same result as `std::stable_sort`, because the comparison no longer treats the two words as equal.
