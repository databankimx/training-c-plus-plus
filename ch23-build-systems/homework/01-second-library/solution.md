## Solution: Second library

The header declares `square` and the source defines it. The library target `mathutil` builds `mathutil.cpp`, and `target_include_directories` with `PUBLIC` gives `main.cpp` the `src` folder, so `#include "mathutil.h"` works.

The program target links `mathutil` with `target_link_libraries`. The link step then finds the definition of `square` in the library. Without that line, the compile succeeds, because the header declares `square`, but the link fails with an undefined reference: the declaration exists, and no definition is linked in.

For the first extension, adding `cube` to `mathutil.cpp` and `mathutil.h` needs no change to `CMakeLists.txt`, since both files already belong to the library. A new source file would need its name added to the `add_library` line, because CMake doesn't look for source files on its own.

For the second extension, a `PRIVATE` include folder applies only to `mathutil` itself. `main.cpp` doesn't receive the folder, so `#include "mathutil.h"` fails to find the header. The compiler reports that it can't open the file. PUBLIC is what makes the header visible to the programs that use the library.
