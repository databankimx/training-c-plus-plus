## Headers and source files

So far every program has lived in one file. That's fine for a few hundred lines, but a larger program is easier to work with when each class has its own files: a header that says what the class is, and a source file that says how it works. This step splits a class in two, and shows the build finding both.

The program has three files in the step's `src` folder. The header declares the class:

```cpp
class Car {
public:
    Car(std::string makeName, std::string modelName, int yearMade);
    void display() const;

private:
    std::string make;
    std::string model;
    int year;
};
```

The header holds declarations only: the members, and the signatures of the functions. It tells any file that includes it what a `Car` is, and what calls are valid. The source file defines the functions:

```cpp
void Car::display() const {
    std::cout << "Make: " << make << "\n";
    // ...
}
```

The `Car::` prefix names the class each function belongs to, as in the methods chapter. The source file includes the header, so the compiler knows the class's layout when it reads the definitions. `main.cpp` includes the same header, and uses the class without knowing how its methods work.

### The include line

`#include "Car.h"` copies the header's text into the file at that point. The quotes tell the compiler to look in the folder of the including file first. That's why a header in `src` is found without any extra setup. System headers such as `<string>` use angle brackets, which tell the compiler to look in the standard library's folders instead.

### Telling the build about the files

Press **Run**. The build compiles `main.cpp` and `Car.cpp` separately, and then links them into one program. The output is:

```
Make: Ford
Model: Escort
Year: 1986

Make: Nissan
Model: Leaf
Year: 2015

```

The step's CMake file lists both sources:

```cmake
add_executable(program src/main.cpp src/Car.cpp)
```

Each source file becomes an object file, and the linker joins them. A class defined in a header but never given a source file can't be linked, so the build fails when a method is called. That error means the definition is missing, not the declaration.

### Why separate the two

The header is what other code depends on. Once `main.cpp` includes `Car.h`, changing the way `display` prints only means changing `Car.cpp`, and nothing that includes the header needs to change. Keeping the interface in one file and the implementation in another is the main reason for the split.

---

### Quiz

*These questions are written for this course.*

````quiz
What goes in a header file?
○ The complete definitions of every method.
→ Not quite. Definitions go in the source file, and the header holds declarations.
◉ Declarations: the class, its members, and the signatures of its functions.
→ Yes. The header tells other files what the class looks like and what it can do.
○ Only the main function.
→ Not quite. main belongs in a source file, and headers are shared by many files.
````

````quiz
What does `#include "Car.h"` do?
○ It runs the code in Car.h.
→ Not quite. It copies the text of the header into the file, and nothing is run.
◉ It copies the header's text into the including file, so the compiler knows the class.
→ Yes. Including is text insertion, done before the compiler reads the file.
○ It links Car.cpp into the program.
→ Not quite. Linking is done by the build, from the list of source files.
````

---

### Try it in the runner

Remove the `#include "Car.h"` line from `main.cpp`, and press **Run**. The build fails, because `Car` is unknown to `main`. Restore the line before you continue.

Then remove `src/Car.cpp` from the `add_executable` line in `CMakeLists.txt`, and press **Run**. The build fails at the linking stage, with an error about an undefined reference to `Car::display`. The declaration is still there, but no definition is linked in. Restore the line.

---

The header says what a class is, and the source file says how it works. The next step puts a second class in a header of its own, and shows what happens when a header is included twice.
