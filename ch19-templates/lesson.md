## Ch19 · Templates

The same algorithm often works for many types: finding the larger of two values, storing a pair, holding a list. Templates let you write the code once, with the type left as a placeholder, and the compiler generates a version for each type the program uses. This chapter covers function templates, class templates, and the rules that make them work.

The steps are:

* [Function templates](#goto/01-function-templates): a template function, deduction of the type, and naming it explicitly.
* [Class templates](#goto/02-class-templates): a class written once for any type, and why its definition goes in a header.
* [Summary](#goto/03-summary): a recap of the chapter and a short quiz. The homework is listed under the chapter.

---

*The examples and explanations are new. The standard containers from Chapter 14 are class templates, and this chapter explains how they're written.*
