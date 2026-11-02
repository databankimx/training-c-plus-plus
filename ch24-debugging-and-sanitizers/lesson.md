## Ch24 · Debugging and Sanitizers

Writing a program is only part of the work. Bugs appear when the program runs, and the tools in this chapter help find them: stack traces that show how a program reached an error, assertions that stop at the first broken promise, a debugger that shows values as they change, and sanitizers that report memory mistakes. Each tool suits a different kind of problem, and this chapter shows where each one fits.

The steps are:

* [Stack traces](#goto/01-stack-traces): capturing the call stack with `std::stacktrace`, and reading it with the Backtrace option.
* [Assertions](#goto/02-assertions): checking conditions that must always hold, and why they're removed in release builds.
* [Finding bugs](#goto/03-finding-bugs): a bug hunt with the VS Code debugger, and the off-by-one error.
* [Sanitizers](#goto/04-sanitizers): the compiler's runtime checks for memory and undefined behavior, and what this toolchain supports.
* [Summary](#goto/05-summary): a recap of the chapter and a short quiz. The homework is listed under the chapter.

---

*The examples and explanations are new. The sanitizer step is explanation only, because the course toolchain doesn't package the sanitizer libraries.*
