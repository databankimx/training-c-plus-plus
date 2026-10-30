## Solution: Greeting card

The example reads the name first, with `std::getline`, because `std::cin >>` would stop at the first space in a name like `Grace Hopper`. It reads the age second, with `cin >>`, which is safe at that point, since the name's newline has already been consumed by `getline`.

The age is printed as `age + 1`, which is a calculation done in the output statement. The variable itself keeps the age the user typed. If the program needed next year's age for later use, it would store the result in its own variable.

Both prompts use `std::flush`, as in the lesson, so each question appears before the program waits.
