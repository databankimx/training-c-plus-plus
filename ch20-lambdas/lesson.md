## Ch20 · Lambdas

Many programs need a small piece of behavior in one place: a rule for sorting, a test for filtering, or an action to repeat over a list. Writing a separate named function for each would scatter the rule away from the code that uses it. A lambda is an unnamed function written where it's needed, and it can use the variables around it through its capture list. This chapter covers the syntax, the comparison rule for sorting, and how captures work.

The steps are:

* [Lambda basics](#goto/01-lambda-basics): writing a lambda, and using one as the comparison for `std::sort`.
* [Captures](#goto/02-captures): capturing a copy or a reference, and the lifetime rule for references.
* [Summary](#goto/03-summary): a recap of the chapter and a short quiz. The homework is listed under the chapter.

---

*The examples and explanations are new. The sort comparison from the standard library step is the first lambda the course has used.*
