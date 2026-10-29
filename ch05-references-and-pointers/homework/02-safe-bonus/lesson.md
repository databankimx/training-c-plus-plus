## Homework: Safe bonus

Write a function that adds a bonus to a score, but only when there's a score to add it to.

The program should:

* define `addBonus`, which takes an `int` pointer to a score and an `int` bonus
* inside `addBonus`, add the bonus to the score when the pointer isn't `nullptr`
* print `No score to update.` when the pointer is `nullptr`, and change nothing
* in `main`, declare `int points = 50;`, then call `addBonus` with the address of `points` and a bonus of 10
* print `Points: 60`, then call `addBonus` with `nullptr` and a bonus of 5, and check that nothing changes

The order of the check matters. The pointer must be checked before it's dereferenced, since reading through a null pointer is undefined.

### What to check

Run the program and compare the output with these lines:

```
Points: 60
No score to update.
Points: 60
```

The last line should show 60 again, since the second call changed nothing. If it shows 65 or any other value, check the `nullptr` branch.

### Extensions

* Change `addBonus` to refuse a negative bonus, and print a message when it does. Think about whether the check belongs before or after the null test.
* Add a second call that passes the address of a second score, `int rank = 3;`, and check that only that score changes.

---

*This exercise is not from the book. It practices the ideas in Chapter 5.*
