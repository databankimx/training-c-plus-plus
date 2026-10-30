## Summary: Functions

This chapter covered how a program is divided into named pieces, and how those pieces pass values in and out.

* **A function is a named block of code.** Its definition gives the return type, the name, the parameters, and the body.
* **A declaration tells the compiler a name exists.** A call must come after a declaration, or after the definition itself.
* **Parameters receive arguments.** Arguments must match the parameters in number and type. A default value makes an argument optional, and defaults must come at the end of the list.
* **`return` sends a value back, and ends the function.** A `void` function returns nothing.
* **Overloads share a name.** They must differ in their parameters, not just their return type. An ambiguous call is refused.
* **An array parameter receives a pointer to its first element.** Pass the size as a separate argument, and expect changes to the array to reach the caller.
* **Reference parameters let a function change its caller's variables.** A `&` in the parameter list makes the parameter another name for the caller's variable. Copies are the default.
* **Recursion handles a problem by calling itself on smaller parts.** It needs a point where the calls stop, and a finite problem, such as a folder tree, guarantees that.

### Check your understanding

*These questions are written for this course.*

````quiz
What must be true before `main` can call a function defined below it?
○ The function must return a value.
→ Not quite. The return type has nothing to do with where a function is declared.
◉ The compiler must have seen a declaration or the definition before the call.
→ Yes. The compiler reads from top to bottom, so the name must be known at the call.
○ The function must have no parameters.
→ Not quite. Functions can have parameters, as long as the call matches them.
````

````quiz
Which declaration is correct for a function that takes a name and an optional count?
○ void f(int count = 1, std::string name);
→ Not quite. A parameter with no default can't come after one with a default.
◉ void f(std::string name, int count = 1);
→ Yes. The defaulted parameter comes last.
○ void f(std::string name = "x", int count);
→ Not quite. The same ordering rule applies here too.
````

````quiz
A recursive function calls itself on a folder's subfolders. What stops the recursion?
○ A counter with a fixed limit.
→ Not quite. The tree may be deeper or shallower than any fixed limit.
◉ The tree is finite, so each branch reaches files, which don't call the function again.
→ Yes. The recursion ends where the tree does.
○ The function returns a value at the first subfolder.
→ Not quite. The listing function doesn't return a value, and it visits every subfolder.
````
