## Homework: Employee pay

Write an `Employee` class and a `Manager` class derived from it, so that each kind of employee computes its own pay, and a single function prints any employee's pay.

The program should:

* define `Employee`, with a `protected` member `monthlySalary` of type `int`, a constructor that takes the salary, and a `virtual` method `pay` that is `const` and returns `monthlySalary`
* define `Manager`, derived from `Employee`, with a constructor that takes a salary and a `bonus`, stores the bonus as a `private` member, and overrides `pay` to return the salary plus the bonus. The constructor passes the salary to the base class with the form `: Employee(salary)`, which the constructors chapter explains.
* define `printPay`, which takes a `const Employee&` and prints `Monthly pay: ` followed by the value of `pay()`
* in `main`, create an `Employee` with a salary of 3000, a `Manager` with a salary of 4500 and a bonus of 800, and print the pay for each with `printPay`

### What to check

The output should be:

```
Monthly pay: 3000
Monthly pay: 5300
```

The second line uses the manager's version of `pay`, even though `printPay` only knows about `Employee`. If it prints 4500, the `virtual` keyword is missing.

### Extensions

* Make `bonus` a `protected` member instead, and add a third class, `Director`, derived from `Manager`, that adds a further amount. Think about which class's `pay` should be used, and how `Director` reaches the bonus.
* Make `printPay` take the `Employee` by value instead of by reference, and check the output. Explain what changed, using the word slicing from the lesson.

---

*This exercise is not from the book. It practices the ideas in Chapter 12.*
