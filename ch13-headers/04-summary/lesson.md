## Summary: Headers and multiple files

This chapter covered how a program is split across files, so each class has an interface and an implementation.

* **A header declares, and a source file defines.** The header holds classes, members, and function signatures. The source file holds the function bodies.
* **`#include "name.h"` inserts a header's text.** Quotes look in the including file's folder first. Angle brackets look in the system folders.
* **Every source file goes in the build.** Each `.cpp` file is compiled separately and then linked. A declared function without a definition causes a link error.
* **Include guards stop double definitions.** `#ifndef`, `#define`, and `#endif` make a header safe to include more than once.
* **Headers should not contain `using namespace`.** A header is included everywhere, so a `using` line in it changes every file that includes it.
* **Inheritance uses the base's constructor.** The colon form passes arguments to the base before the derived class's body runs.
* **Include what the declarations need.** A header includes the headers for the types it uses, and nothing more.

### Check your understanding

*These questions are written for this course.*

````quiz
Which file should hold the body of a member function?
○ The header.
→ Not quite. Headers declare, and the bodies go in a source file.
◉ The source file for that class.
→ Yes. The source file defines what the header declares.
○ The main file, always.
→ Not quite. Each class's functions usually live in that class's own source file.
````

````quiz
What happens if a header has no include guard, and a file includes it twice?
○ The second copy is ignored.
→ Not quite. Without a guard, the compiler reads both copies.
◉ The class is defined twice, and the build fails.
→ Yes. A class may only be defined once in a translation unit.
○ The program runs twice.
→ Not quite. The problem is at compile time, and the program never runs.
````

````quiz
A declared function is called, but no source file defines it. At which stage does the build fail?
○ Preprocessing.
→ Not quite. Preprocessing only inserts headers and handles guards.
○ Compiling each file.
→ Not quite. Each file compiles on its own, and it's allowed to call a declared function.
◉ Linking.
→ Yes. The linker can't find a definition for the function, and reports an undefined reference.
````
