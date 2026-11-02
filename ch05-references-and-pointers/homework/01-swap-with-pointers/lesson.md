## Homework: Swap with pointers

The functions chapter swapped two numbers with reference parameters. In this exercise you'll write the same swap with pointers, so you can see how the two versions compare.

The program should:

* ask for two integers, `a` and `b`, with the prompts `Enter a: ` and `Enter b: `, and read them with `std::cin`
* define `swapValues`, which takes two `int` pointers, and swaps the values they point to
* call `swapValues` from `main`, passing the addresses of `a` and `b`
* print the values as `a = 8, b = 3`, after the swap

Use `std::flush` on each prompt. Inside `swapValues`, use `*` to read and write the values. Don't use a reference parameter, since that's the other version.

### What to check

Try these inputs, and compare the output with the answers:

* `3` and `8` should print `a = 8, b = 3`
* `5` and `5` should print `a = 5, b = 5`
* `-2` and `7` should print `a = 7, b = -2`

Check the second case as well. A swap of two equal values changes nothing, and that's correct.

### Extensions

* Write `swapValues` so it works when either pointer is `nullptr`, and does nothing in that case. Explain why the check has to come before the swap.
* Compare your `swapValues` with the reference version from the functions chapter. Which one reads more clearly to you, and which one would make a mistake easier to spot?

---

*This exercise is not from the book. It practices the ideas in Chapter 5.*
