## Summary: Lambdas

This chapter covered lambdas, unnamed functions written where they're used, and the captures that let them use the variables around them.

* **A lambda is a function written in place.** `[](int x) { return x * x; }` has parameters and a body, and it can be stored with `auto`.
* **A lambda can be a comparison for the standard sort.** The comparison answers whether one value comes before another.
* **A sort comparison must be a strict order.** `<` and `>` work. `<=` doesn't.
* **A capture by copy holds its own value.** Later changes to the original don't reach the lambda.
* **A capture by reference uses the original.** Each call sees and changes the current value.
* **A lambda must not outlive what it captures by reference.** Calling it afterward is undefined behavior.
* **Name each capture.** `[=]` and `[&]` work, but they hide what the lambda depends on.

### Check your understanding

*These questions are written for this course.*

````quiz
What does the capture `[&count]` mean?
○ The lambda holds a copy of count.
→ Not quite. A copy is written `[count]`, without the ampersand.
◉ The lambda refers to the original count, so changes it makes are visible outside.
→ Yes. The ampersand means capture by reference.
○ The lambda is not allowed to use count.
→ Not quite. A capture is how a lambda gets access to count.
````

````quiz
Which comparison is valid for sorting a list in descending order?
○ a <= b
→ Not quite. A non-strict comparison can make the sort misbehave.
◉ a > b
→ Yes. It's a strict order, with the larger values first.
○ a == b
→ Not quite. Equality doesn't order values.
````

````quiz
Why is `[=]` less clear than naming each capture?
○ Because it makes the lambda slower.
→ Not quite. The cost is in reading the code, not in running it.
◉ Because it hides which variables the lambda depends on.
→ Yes. Naming each capture shows the dependencies in one place.
○ Because it can't be used with the standard library.
→ Not quite. It can be used, but it makes the lambda harder to read.
````
