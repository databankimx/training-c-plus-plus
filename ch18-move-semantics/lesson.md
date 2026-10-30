## Ch18 · Move Semantics

Copying an object is the default in C++, and it's the right choice when two objects each need their own value. Often the source is about to be discarded, though, and copying it is wasted work. This chapter covers moving, which transfers an object's contents instead, and the ownership rules that make moves safe.

The steps are:

* [Copies and moves](#goto/01-copies-and-moves): the copy and move constructors, `std::move`, and the moved-from state.
* [Moving ownership](#goto/02-moving-ownership): transferring a `unique_ptr`, which can only be moved.
* [Summary](#goto/03-summary): a recap of the chapter and a short quiz. The homework is listed under the chapter.

---

*The examples and explanations are new. They build on the smart pointers from Chapter 17.*
