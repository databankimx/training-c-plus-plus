## Homework: Bank account

Write a class that represents a bank account, with a private balance and checked operations on it.

The class should:

* have a constructor that takes an opening balance, and throws a `std::invalid_argument` with the message `opening balance cannot be negative` when it's below zero
* have a `deposit` method that takes an amount, and throws a `std::invalid_argument` with the message `Deposit must be positive.` when the amount is zero or less
* have a `withdraw` method that takes an amount, and throws a `std::runtime_error` with the message `Insufficient funds.` when the amount is more than the balance
* have a `getBalance` method that returns the balance, and is declared `const`
* keep the balance private

In `main`, create an account with an opening balance of 0.0, then:

* deposit 100.0 and withdraw 30.0, then print `Balance: 70.00`
* try to withdraw 500.0, and print the message from the exception
* try to deposit -5.0, and print the message from the exception
* print the balance again, with two decimal places

Use `std::fixed` and `std::setprecision(2)` for the printed balances.

### What to check

The output should be:

```
Balance: 70.00
Insufficient funds.
Deposit must be positive.
Balance: 70.00
```

The last line should match the first. A failed withdrawal or deposit must leave the balance unchanged, and that's the most important rule in the exercise.

### Extensions

* Add a `transfer` method that moves money from one account to another. Think about what should happen if the withdrawal succeeds and the deposit then fails.
* Store a transaction count in the class, and increase it on each successful deposit or withdrawal. Keep it private, and provide a getter.

---

*This exercise is not from the book. It practices the ideas in Chapter 11, with the exceptions from Chapter 9.*
