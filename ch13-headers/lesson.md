## Ch13 · Headers and Multiple Files

Real programs are too large for one file. This chapter covers how to split a program into headers and source files, how the build brings them together, and how include guards keep a header safe to use from many places. It finishes Part I, which has now covered the language from the first program to classes, inheritance, and multi-file programs.

The steps are:

* [Header and source](#goto/01-header-and-source): splitting a class into a header and a source file, and the build that joins them.
* [Include guards](#goto/02-include-guards): guarding a header against being included twice.
* [Combining classes](#goto/03-combining-classes): inheritance and composition across three classes and seven files.
* [Summary](#goto/04-summary): a recap of the chapter and a short quiz. The homework is listed under the chapter.

---

*The examples in this chapter are adapted from the earlier C++ tutorial. The headers have been rewritten to avoid `using namespace`, and the explanations are new.*
