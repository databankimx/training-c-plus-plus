## Summary: References and pointers

This chapter covered two ways to refer to a variable without copying it, and how pointers connect to arrays.

* **A reference is another name for a variable.** It's declared with `&` after the type, must be set up when declared, and always refers to the same variable.
* **A pointer holds an address.** It's declared with `*` after the type, and can be reassigned or set to `nullptr`.
* **`&` takes an address, and `*` reads through it.** In an expression, `&x` is the address of `x`, and `*ptr` is the value at the address `ptr` holds.
* **Check a pointer before reading through it.** A null pointer has no value, and dereferencing it is undefined behavior.
* **An array's name is a pointer to its first element.** `numbers[i]` is the same as `*(numbers + i)`.
* **Adding to a pointer moves it by elements.** `first + 2` is two elements along, whatever the size of the element.

### Check your understanding

*These questions are written for this course.*

````quiz
Which declaration gives `ptr` the ability to be empty?
○ int& ptr = x;
→ Not quite. A reference can't be empty, so it can't stand for "no target".
◉ int* ptr = nullptr;
→ Yes. A pointer can hold nullptr when it points at nothing.
○ int ptr = &x;
→ Not quite. That declares an int, and the & gives an address that an int can't hold.
````

````quiz
After `int numbers[4] = {1, 2, 3, 4};` and `int* p = numbers;`, what is `*(p + 3)`?
○ 1
→ Not quite. That's *p, the first element.
◉ 4
→ Yes. Adding 3 moves the pointer three elements along, to the fourth element.
○ 3
→ Not quite. That's the third element, at p + 2.
````

````quiz
What does the `&` mean in `int& r = n;`?
○ It takes the address of n, and stores it in r.
→ Not quite. That describes a pointer. A reference is another name for n.
◉ It declares r as a reference, so r is another name for n.
→ Yes. In a declaration, & makes a reference.
○ It divides n by r.
→ Not quite. Division uses /, and & here is part of the declaration.
````
