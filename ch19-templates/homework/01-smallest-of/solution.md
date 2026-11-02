## Solution: Smallest of

The template takes its vector by `const` reference. That avoids copying the vector, and the `const` promises that the function won't change it. `T` is deduced from the vector's element type, so the same definition serves `std::vector<int>` and `std::vector<std::string>`.

The function starts with the first value as the smallest, then compares each later value with the current smallest. The comparison `<` is the operator that both `int` and `std::string` provide, which is why the same code works for both. A string comparison is alphabetical, so `apple` is smaller than `fig` and `pear`.

For the first extension, a largest-value template is the same loop with `>` in place of `<`. For the empty vector, `values[0]` reads past the end, which is undefined behavior. A template can't fix that, because the type doesn't know whether the vector has values. The fix belongs in the function: check `values.empty()` first, and either return a value that means "none" or report the error, for example with an exception.
