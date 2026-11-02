## Ch05 · References and Pointers

Arrays gave you a list of values under one name. This chapter covers two ways a program refers to a variable without copying it: references, which are another name for a variable, and pointers, which hold the address of one. Both connect back to arrays, since an array's name is a pointer to its first element, and both are the foundation for passing data to functions without copying it.

The steps are:

* [References](#goto/01-references): what `&` means in a declaration, and how a reference behaves.
* [Pointers](#goto/02-pointers): taking an address, reading through a pointer, and empty pointers.
* [Pointers and arrays](#goto/03-pointers-and-arrays): why an array's name works as a pointer, and what adding to a pointer does.
* [Summary](#goto/04-summary): a recap of the chapter and a short quiz. The homework is listed under the chapter.

---

*The examples in this chapter are adapted from the earlier C++ tutorial. The explanations are new.*
