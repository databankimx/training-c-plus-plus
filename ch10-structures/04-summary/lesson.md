## Summary: Structures

This chapter covered grouping related values into one type.

* **A structure declaration creates a type.** `struct Car { ... };` describes what a car holds, and variables of type `Car` are created from it.
* **Members are reached with a dot.** `car.year` is the year member of the variable `car`.
* **Each member has its own type.** The compiler checks every assignment and every initial value against it.
* **Structures can be passed and returned.** A function can build one, and return it as a value.
* **A parameter copies unless it's a reference.** `describe(Car car)` works on a copy, and `makeOlder(Car& car)` changes the caller's structure.
* **Members can have default values.** A variable that doesn't set a member takes its default.
* **Brace initialization sets members in order.** `Settings b{"Scott", 9, true};` matches values to members in the order they're declared.
* **A copy is independent.** Changing a copy doesn't change the structure it came from.
* **A structure can have constructors.** A constructor changes how brace initialization works, so the classes chapter covers constructors in full, along with the access rules that go with them.

### Check your understanding

*These questions are written for this course.*

````quiz
Which declaration gives a structure a default for its volume member?
○ int volume(5);
→ Not quite. That's a constructor-style syntax this course hasn't covered, and it isn't a member default.
◉ int volume = 5;
→ Yes. A member with an initializer uses it when a variable doesn't set the member.
○ default volume = 5;
→ Not quite. default isn't a keyword for this purpose.
````

````quiz
A function receives a structure by value and changes one member. What does the caller see?
○ The change, because structures are always shared.
→ Not quite. A value parameter is a copy, so the caller doesn't see the change.
◉ Nothing, because the function changed a copy.
→ Yes. Only a reference parameter lets a function change the caller's structure.
○ An error, because copies can't be changed.
→ Not quite. A copy can be changed, but the change stays inside the function.
````

````quiz
In `Settings b{"Scott", 9, true};`, what does the value 9 initialize?
○ The name member.
→ Not quite. The first value goes to name.
◉ The volume member, the second one declared.
→ Yes. Brace initialization matches values to members in declaration order.
○ The muted member.
→ Not quite. muted receives the third value, true.
````
