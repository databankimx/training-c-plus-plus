## Ch12 · Inheritance and Polymorphism

Many classes share most of their behaviour, and some code needs to treat different objects in the same way. This chapter covers inheritance, which lets one class build on another, and polymorphism, which lets one call do the right thing for each object it's given. Together they're the usual way to organize larger C++ programs.

The steps are:

* [Inheriting members](#goto/01-inheriting-members): deriving a class from a base, inheritance chains, and the public inheritance keyword.
* [Protected and multiple](#goto/02-protected-and-multiple): protected members, and a class with more than one base.
* [Polymorphism](#goto/03-polymorphism): `virtual` and `override`, and calling through a base reference.
* [Summary](#goto/04-summary): a recap of the chapter and a short quiz. The homework is listed under the chapter.

---

*The inheritance examples are adapted from the earlier C++ tutorial. The polymorphism step is new: the tutorial's version calls ordinary functions, so it doesn't demonstrate polymorphism.*
