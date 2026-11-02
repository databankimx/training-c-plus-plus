## Summary: Templates

This chapter covered writing code once for many types, with the compiler generating a version for each type the program uses.

* **A function template has a type parameter.** `template <typename T>` introduces `T`, which stands for a real type in each generated version.
* **The compiler deduces the type from the arguments.** Arguments that disagree about `T` cause an error, and naming the type fixes it.
* **A class template generates a class per type.** `Box<int>` and `Box<std::string>` are separate classes with their own member types.
* **Member functions are generated when used.** An error in an unused member may not appear until the member is called.
* **Templates are defined in headers.** The full definition must be visible wherever the template is used, so it goes in the header, not a source file.
* **The standard containers are class templates.** `std::vector<T>` and `std::map<K, V>` are the same kind of thing as `Box<T>`.

### Check your understanding

*These questions are written for this course.*

````quiz
What does `largerOf(3, 2.5)` do, for `template <typename T> T largerOf(T a, T b)`?
○ It returns 3, converted to a double.
→ Not quite. The compiler doesn't choose a type for you when the arguments disagree.
◉ It fails to compile, because T is deduced as two different types.
→ Yes. Naming the type, as in largerOf<double>(3, 2.5), resolves it.
○ It returns 2.5, since the smaller value is always returned.
→ Not quite. The function returns the larger value, and the compile fails before any value is returned.
````

````quiz
Which statement about a class template is true?
○ It is compiled once and shared by all types.
→ Not quite. Each type gets its own generated class.
◉ Each type it's used with produces a separate class, with its own member types.
→ Yes. Box<int> and Box<std::string> are two different classes.
○ It can only be used with the built-in types.
→ Not quite. It can be used with any type that supports the operations its members use.
````

````quiz
Why must a template's full definition be visible where it's used?
○ Because the compiler checks templates at run time.
→ Not quite. Templates are instantiated at compile time.
◉ Because the compiler generates the version for each type from the full definition.
→ Yes. A declaration alone isn't enough to produce a version.
○ Because templates use more memory than ordinary functions.
→ Not quite. Memory has nothing to do with the rule.
````
