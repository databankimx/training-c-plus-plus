## Homework: Safe age

Write a program that asks for an age, and keeps asking until it gets a valid one. Invalid input is reported with an exception, and the program recovers from it.

The program should:

* ask for an age with the prompt `Enter your age (0-120): `
* read the answer with `std::cin`
* throw a `std::invalid_argument` with the message `not a number` when the input isn't a number, and clear the input so it can be read again
* throw a `std::out_of_range` with the message `age must be from 0 to 120` when the number is outside that range
* catch each exception, print its message with `what()`, and ask again
* when a valid age has been read, print `Age accepted: 42`, with the age that was entered, and end

Use a `while (true)` loop, with `break` once a valid age is read. Use `std::flush` on the prompt.

### What to check

Try these inputs, in this order:

* `abc` should print `not a number` and ask again
* `200` should print `age must be from 0 to 120` and ask again
* `-1` should print the same range message
* `42` should print `Age accepted: 42`

The first input is the important one. Without clearing the stream, the program would print the message over and over, the way the Battleship game did before its fix.

### Extensions

* Add a third check for an age that's valid but unlikely, such as above 100, and throw a different exception for it. Think about which standard class fits best.
* Catch the two exceptions separately, so each one has its own handling. Then compare the two versions: which one is easier to change later?

---

*This exercise is not from the book. It practices the ideas in Chapter 9.*
