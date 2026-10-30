## Ch17 · RAII and Smart Pointers

C++ programs hold resources: files, locks, memory on the heap. Every one has to be released, and releasing them by hand is where bugs come from. This chapter covers RAII, the pattern that ties a resource's release to the lifetime of an object, and the smart pointers that apply the pattern to heap memory.

The steps are:

* [Destructors and scope](#goto/01-destructors-and-scope): when a destructor runs, and why release happens on every way out of a scope.
* [Unique pointers](#goto/02-unique-ptr): a heap object with one owner, created with `std::make_unique`.
* [Shared pointers](#goto/03-shared-ptr): several owners of one object, and how the count decides its release.
* [Summary](#goto/04-summary): a recap of the chapter and a short quiz. The homework is listed under the chapter.

---

*The examples and explanations are new. The file streams from Chapter 8 are the first RAII example the course used.*
