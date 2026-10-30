## Solution: Pair

The class template has two type parameters, separated by a comma in the template line. Each use names both types in the angle brackets, so `Pair<int, std::string>` and `Pair<std::string, double>` are two separate classes, each with a `first` and `second` of the types it was given.

The constructor takes its values by value and copies them into the members. For these simple types that's fine. The getters are `const`, since they only read.

For the first extension, `swapped` on a `Pair<int, std::string>` returns a `Pair<std::string, int>`. The return type is written in terms of the other parameter order, so `Pair<Second, First>` names the new type. The function is only instantiated when it's called, so a `Pair` whose two types can't be swapped only fails if someone calls `swapped` on it.

For the second extension, `Pair<int, int>` is valid because the two parameters are independent names. Each one takes its own type argument, and the two arguments happen to be the same. The compiler generates a class whose two members are both `int`, which is no different from any other use.
