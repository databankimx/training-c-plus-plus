## Solution: Temperature utilities

The header declares the two functions, and the source file defines them. `main.cpp` includes the header, so the calls are checked against the declarations, and the definitions are linked in from `Temperature.cpp`. Neither file needs to know the other's body.

Both formulas use `9.0` and `5.0`, with decimal constants. Writing `9 / 5` with integers would divide first and give 1, which is the same integer-division trap from the arithmetic lesson.

The `-40` line shows the two scales agree at that point, so the value comes back unchanged. If your output shows `-40.00 C is -40.00 F`, both formulas are right at that boundary. Check the other lines for a sign or order mistake.

For the first extension, `kelvinFromCelsius` belongs in the header, as a declaration, and its definition in the source file. The header is the part other files see, so it's where a new function is announced.

For the second extension, without the include, `main.cpp` calls functions it has never seen declared. The compiler reports an undeclared identifier. The header is needed for the declarations, even though the code is in a different file. The linker can't fix a missing declaration, only a missing definition.
