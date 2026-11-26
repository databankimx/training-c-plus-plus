# DataBank IMX - C++ Developer Training

## License and Support

This repository is provided under the [MIT License](LICENSE). You are free to use, copy, modify, merge, publish, distribute, sublicense, and/or sell the materials in this repository, subject to the terms of that license.

This repository is provided for training and reference purposes only. DataBank IMX does not provide warranties, guarantees, maintenance, troubleshooting, implementation assistance, or technical support for this code or its use. Use it in any way permitted by the MIT License, but you are responsible for evaluating, adapting, testing, and supporting any use of it in your own environment.

---

## What is this repository for?

* C++ developer training curriculum for DataBank IMX, covering the language from first programs through the standard library, with a focus on reading and converting existing C++ code
* Chapter-by-chapter lessons, with code you can edit and run, and short quizzes
* A final project: a calculator built in stages, with a core track and a bonus track, each with a worked example
* A desktop lesson runner, built with C++, that lets you read lessons, edit and run each step, and run its tests

---

## Who is this for?

* DataBank IMX developers who need to read, convert, or maintain C++ code
* Developers who are new to C++ and have some experience with another programming language

---

## About

* **Author:** [Scott McLean](mailto:smclean@databankimx.com)
* **Purpose:** Internal developer training curriculum for DataBank IMX

---

## DataBank Responsibilities for Custom Code

All DataBank employees - including those working with AI-assisted tools - are bound by the Development Rules of Engagement, published as the [development-rules-of-engagement.pdf](https://databankimx.sharepoint.com/:b:/r/sites/Hub-PS/DevTools/Policies/development-rules-of-engagement.pdf?d=w1c01477e09e048acbe4c96eba851a183&csf=1&web=1&e=uL7JEw). That document defines the rules for quoting, approving, developing, reviewing, scanning, storing, and delivering custom code for client work.

Key obligations that apply to everyone on every custom code engagement:

* **You own the code you deliver.** This applies equally to hand-written code, AI-assisted code, and AI-generated code. "The AI wrote it" is not an acceptable explanation for a production issue, a failed review, a security finding, or a support problem.
* **Code must be reviewed before delivery.** Review is interactive and must confirm that the code works, meets DataBank standards, is maintainable, and that the developer understands it well enough to explain, debug, and maintain it. Polished or well-formatted output - including AI-generated output - is not evidence of correctness.
* **Code must be in source control before delivery.** All custom code must be committed to the appropriate DataBank GitHub Enterprise repository before it is delivered to a client, regardless of whether the client receives source code, compiled binaries, or deployed functionality.
* **CI scanning must pass before delivery.** Required checks are the standards policy scan, SonarQube, and Snyk. A passing local build is not a substitute.
* **All third-party dependencies must be license-vetted.** The license must permit closed-source commercial use. Copyleft or unclear licensing must be escalated before use. Dependencies must not be added simply because an AI tool suggested them.
* **Only approved AI tools may be used.** Use only IT-approved tools through company accounts. All data entered into AI systems is subject to the [DataBank AI Acceptable Use Policy](https://workforcenow.adp.com/mascsr/wfncontenttools/file-management/file/JTJGc3RhdGljJTJGY2xpZW50cyUyRmNvbnRlbnQlMkZBSStBY2NlcHRhYmxlK1VzZStQb2xpY3kucGRmJTNGMTc3MTM0NzA4NjE4MQ==) and must be treated as confidential by default.
* **Custom code is billable work.** Code must be tied to an approved quote or engagement before commitment or delivery. Development quotes require approval from the Development Director or delegated development leadership before being sent externally.
* **Exceptions require explicit approval.** Time pressure alone is not a reason to bypass quote approval, source control, review, or CI scanning.

See the Development Rules of Engagement linked above for the full policy, including billing and quoting rules, source-code delivery rules, the delivery readiness checklist, and the exception process.

> Policy document links point to DataBank internal locations. They may not open for readers outside DataBank IMX.

---

## Textbook reference

The lessons follow two references. Both are free, and both are linked from the lessons that use them.

* [Learn C++](https://www.learncpp.com/), by Alex Allain. A complete, free course, organized in the order the lessons follow.
* *A Tour of C++*, third edition, by Bjarne Stroustrup (Addison-Wesley). A short guide to the language, written by its designer, used in the modern-features chapters.

Lessons quote only the short examples they need from these references, and explain the rest in their own words.

---

## Setup and requirements

* **Windows 10 or 11**, with the WebView2 runtime (included with Windows 11)
* **MSYS2**, with the UCRT64 toolchain: g++ 14 or later, CMake, and Ninja
* **VS Code** with the C/C++ extension (recommended), or any editor you prefer

See [QUICKSTART.md](QUICKSTART.md) for a step-by-step guide.

### Quick start

From the repository root, in PowerShell:

```pwsh
powershell -NoProfile -ExecutionPolicy Bypass -File .\setup.ps1 -InstallMissing
```

The script checks the toolchain, downloads the WebView2 SDK and nlohmann/json into `resources\vendor`, makes the runner's icon, and builds the runner. It's safe to run more than once.

Then start the lesson runner:

```pwsh
cd lesson-runner
.\build\host\lesson-runner.exe
```

### Libraries used by the course

| Library | Where | Purpose | License |
|---|---|---|---|
| g++ (MSYS2 UCRT64) | Lessons and runner | Compiles every lesson program | GPL with the GCC runtime exception |
| CMake | Lessons and runner | Builds each step | BSD-3-Clause |
| Ninja | Lessons and runner | Runs the build | Apache 2.0 |
| WebView2 SDK | Lesson runner | The runner's window | Microsoft SDK license |
| nlohmann/json | Lesson runner | Messages between the window and the back end | MIT |
| marked | Lesson runner (web folder) | Converts lesson Markdown to HTML | MIT |
| @viz-js/viz | Lesson runner (web folder) | Draws the diagrams in lessons | MIT, which wraps Graphviz (EPL-2.0) |
| highlight | Lesson runner (web folder) | Syntax coloring in the Source and Lesson panes | MIT |
| ImageMagick, librsvg | Setup only | Makes the runner's icon from the SVG logo. Not linked into any program | Apache 2.0 and LGPL-2.1, used as separate tools |

---

## Third Party Licenses

The runner itself links only the MIT, BSD, Apache, and Microsoft-licensed components listed above. The GCC runtime exception and the Graphviz (EPL-2.0) license need review before commercial deployment. The licensing rules are in the [Development Rules of Engagement](https://databankimx.sharepoint.com/:b:/r/sites/Hub-PS/DevTools/Policies/development-rules-of-engagement.pdf?d=w1c01477e09e048acbe4c96eba851a183&csf=1&web=1&e=uL7JEw) (internal only).

---

## Using VS Code

The lessons work in any editor, but this section covers Visual Studio Code, which the course is written for. The steps are also in [QUICKSTART.md](QUICKSTART.md).

### Install the extension

Open a `.cpp` file from a lesson. VS Code offers to install the **C/C++ Extension Pack** (publisher Microsoft). Accept it, or install it from the Extensions view by searching for "C/C++ Extension Pack".

The pack includes CMake Tools. When it asks for a kit, choose **GCC 16.2.0 x86_64-w64-mingw32 (ucrt64)**, the MSYS2 compiler the course uses. Don't choose **[Scan for kits]** or **[Unspecified]**, since they can select a different compiler.

CMake Tools may report that it activated the runner's project in `lesson-runner`. That message is informational, and you can dismiss it.

Restart VS Code after `setup.ps1` has run, so it picks up the MSYS2 folder on your user PATH. Open the repository root in VS Code, not a sub-folder.

### Single-file lessons

Open the lesson's `.cpp` file, then:

* **Build:** Ctrl+Shift+B.
* **Build and run:** Terminal > Run Task > `C/C++: run active file`. The program's output appears in the terminal.
* **Debug:** press F5, and choose `Debug active C++ file (MSYS2 gdb)`. Click in the gutter first, if you want a breakpoint.

These compile only the file that's open, so they work for lessons with one source file.

### Multiple-file lessons

Some lessons use more than one source file, such as Chapter 13 (headers). The build and run tasks compile only the open file, so they report `undefined reference` errors for functions in the other files. That's expected.

Build and run these lessons through the lesson runner: open the step and press **Run**. The runner builds every file the step's `CMakeLists.txt` lists.

In VS Code, open any `.cpp` file in the step's `src` folder, then use Terminal > Run Task:

* `C/C++: build lesson (CMake)` configures and builds the step's project.
* `C/C++: run lesson (CMake)` builds it, then runs the program.

To build from a terminal instead, open a terminal in the step's folder and run:

```pwsh
cd C:\Development\training\training-c-plus-plus\ch13-headers\02-include-guards
cmake -S . -B build -G Ninja -DCMAKE_CXX_COMPILER=g++
cmake --build build
.\build\program.exe
```

Replace the `cd` path with the step's own folder. The `-S .` argument must point at the folder that holds the step's `CMakeLists.txt`.

### Messages you can ignore

* `"main.cpp" not found in ... compile_commands.json ... c_cpp_properties.json will be used`. The editor's settings cover the lesson's files, so this is informational.
* `CMake Tools detected and activated the project`. This is informational.

### Troubleshooting

| What you see | What to do |
|---|---|
| `The preLaunchTask ... terminated with exit code -1` | Restart VS Code. Setup adds the MSYS2 folder to your user PATH, and VS Code only sees that after a restart. |
| `libgcc_s_seh-1.dll was not found` | The MSYS2 folder isn't on your user PATH. Run `setup.ps1 -InstallMissing` again, then restart VS Code. |
| `undefined reference to ...` in a single-file build | The lesson has more than one source file. Build it through the lesson runner, or use the CMake tasks above. |
| The debug list shows only `(Windows) Launch`, or no gdb | gdb isn't installed. Run `setup.ps1 -InstallMissing` again. |
| The kit list shows only Scan, Unspecified, or a different GCC | Choose the GCC 16.2.0 ucrt64 kit. If it isn't listed, run the kit scan from the CMake Tools menu, then choose it. |

---

## Running the training

### Lesson Runner

The lesson runner is a desktop window, built with C++ and WebView2. It lets you browse chapters, read lessons, edit and run each step, and run its tests. Setup is in [QUICKSTART.md](QUICKSTART.md).

#### Finding lessons

The chapter list on the left shows each chapter, such as *Ch01 · Getting Started*. Click a chapter to show its steps, then click a step to open it.

* Chapters are listed in order. The final project comes after the numbered chapters.
* Each step is one folder. A step with a `CMakeLists.txt` has code you can run.
* Homework appears under its chapter, in its own list.

#### Reading and running a step

* The **Lesson** tab shows the step's lesson, with quizzes.
* The **Source** tab shows the step's `src/main.cpp`. It's an editor. Edits are kept in the runner until you click **Reset**, and nothing is written to the repository.
* Press **Run** (or F5) to build and run the step. The build status lines appear in the Output pane, followed by the program's output.
* Press **Test** to build the step and run its tests, for steps that have them.
* If a program asks for input, type in the input box under the Output pane, then press Enter or click **Go**.
* Press **Escape**, or click **Stop**, to stop a run. The Run button becomes Stop while a program runs.
* The **Backtrace** checkbox builds with stack-trace support, so a `std::stacktrace` in a step shows function names.
* Steps that declare options in their `CMakeLists.txt` show a checkbox for each option, next to Backtrace. Each checkbox starts at the default the step declares. Choices are kept while you move between steps, and reset when the runner restarts.

#### Quick picks

Each step's `commands.txt` lists quick picks. Choosing one fills the input box. A pick is either `run` or `test`, optionally followed by arguments for the program.

#### Homework and spoilers

Homework steps ask you to write your own program first. The Run button stays disabled until you choose **Show example (spoiler)**. Once you do, the example is available, and Run is enabled. Try the exercise before you reveal the example, since most of the learning happens while you're stuck.

#### Keyboard shortcuts

| Key | Action |
|---|---|
| F5 | Run the current step |
| Escape | Stop a running program, or cancel the input |

#### Troubleshooting

* **The window doesn't open:** check that the toolchain is in `C:\msys64\ucrt64\bin`, and run `setup.ps1` again.
* **Run says it could not start a build tool:** the MSYS2 toolchain isn't installed, or isn't in that folder.
* **A step says it didn't build a program:** the step's `CMakeLists.txt` should build an executable called `program`.
* **The first build is slow:** normal. Later builds are faster.

The runner's source code is in `lesson-runner/host` (the C++ back end) and `lesson-runner/web` (the page).

### Running lessons directly

Each step with code is a CMake project. From a terminal, in the step's folder:

```pwsh
cd C:\Development\training\training-c-plus-plus\ch13-headers\02-include-guards
cmake -S . -B build -G Ninja -DCMAKE_CXX_COMPILER=g++
cmake --build build
.\build\program.exe
```

---

## Repository structure

```
training-c-plus-plus/
|- ch01-getting-started/         - Chapter 1: setup, the first programs, and the summary
|- ch02-variables-and-input/     - Chapter 2: variables, arithmetic, strings, and input
|- ch03-decisions/               - Chapter 3: booleans, logical operators, if statements, and switch
|- ch04-arrays/                  - Chapter 4: declaring, initializing, and multidimensional arrays
|- ch05-references-and-pointers/ - Chapter 5: references, pointers, and pointers with arrays
|- ch06-loops/                   - Chapter 6: loops, break and continue, and a Battleship game
|- ch07-functions/               - Chapter 7: functions, parameters, return values, arrays, reference parameters, and recursion
|- ch08-files/                   - Chapter 8: writing, reading, and overwriting files
|- ch09-exceptions/              - Chapter 9: throwing values, error codes, and standard exceptions
|- ch10-structures/              - Chapter 10: structures, structures in functions, and initializing structures
|- ch11-classes/                 - Chapter 11: classes, methods, constructors, and encapsulation
|- ch12-inheritance/             - Chapter 12: inheritance, protected members, and polymorphism
|- ch13-headers/                 - Chapter 13: headers, include guards, and multiple files
|- ch14-containers/              - Chapter 14: vectors, maps, unordered maps, and choosing a container
|- ch15-efficiency/              - Chapter 15: counting operations, Big-O, and Fibonacci with and without memory
|- ch16-searching-and-sorting/   - Chapter 16: linear and binary search, the sorts, and the standard library versions
|- ch17-raii-and-smart-pointers/ - Chapter 17: destructors, unique and shared pointers, and RAII
|- ch18-move-semantics/          - Chapter 18: copies and moves, std::move, and moving ownership
|- ch19-templates/               - Chapter 19: function templates and class templates
|- ch20-lambdas/                 - Chapter 20: lambda basics, captures, and comparisons for the standard algorithms
|- ch21-testing/                 - Chapter 21: checking results, running tests with CTest
|- ch22-concurrency/             - Chapter 22: threads, join, mutexes, and lock_guard
|- ch23-build-systems/           - Chapter 23: library targets, and options
|- ch24-debugging-and-sanitizers/ - Chapter 24: stack traces, assertions, the debugger, and sanitizers
|- ch25-modern-features/         - Chapter 25: auto, structured bindings, and std::optional
|- final-project/                - The final project: a calculator, with a core and bonus items as homework steps
|- lesson-runner/                - The desktop lesson runner
|  |- host/                      - C++ back end: window, router, runner, discovery
|  |- web/                       - The page: HTML, CSS, JavaScript, and the vendored libraries
|- resources/                    - Setup documents, snippets, vendored downloads, and the runner's test steps
|- setup.ps1                     - Prepares everything the runner needs
|- QUICKSTART.md                 - Step-by-step setup guide
|- AUTHORING.md                  - How to write and check lessons
```

Each chapter folder holds its sections, and each section holds its steps. A step is a folder with a `lesson.md`, and a `CMakeLists.txt` if it has code. Steps appear in the order of their names, so the number prefix keeps them in order.

### Chapters

* Part I, Basics: getting started, variables and input, decisions, arrays, references and pointers, and loops (Chapters 1 to 6)
* Part II, Structuring programs: functions, files, exceptions, structures, classes, inheritance and polymorphism, and headers and multiple files (Chapters 7 to 13)
* Part III, Additional topics: containers, efficiency, searching and sorting, RAII and smart pointers, move semantics, templates, lambdas, testing, concurrency, build systems, debugging and sanitizers, and modern features (Chapters 14 to 25)
* Final project: a calculator in two tracks, a core and bonus items, placed at the end of Part III

---

## Known conflicts and compatibility notes

* The lesson runner and the setup script run on Windows only. They need the MSYS2 UCRT64 toolchain.
* The VS Code steps are written for Visual Studio Code. The lessons and the runner work in any editor, but you'll need to find the matching build and debug steps in your editor's documentation.
* Some lessons have more than one source file. A single-file build or run reports `undefined reference` errors for them. Build these through the lesson runner or the CMake tasks.

---

## Authorship note

This training curriculum was developed for internal use at DataBank. As with the other training repositories, I used generative AI in places for code review, cleanup, and turning rough notes into readable documentation.

~ Scott McLean, 2026

---

## Release version

| Date | Changes |
|---|---|
| 11/07/2026 | Setup script and VS Code tasks: setup.ps1 installs Git and MSYS2 when asked, clones the repository, adds the MSYS2 folder to the user PATH, and installs gdb. The C++ build, run, and debug tasks and the multi-file CMake tasks are included. Chapter 24's sanitizers lesson uses GCC's static analyzer (-fanalyzer). The runner's modified flag ignores line-ending differences |
| 10/30/2026 | Version 1.0: the first complete edition, covering Parts I to III, with the final project as homework steps under spoiler guards, and the lesson runner. The runner reads each step's CMake options into checkboxes, and labels homework from a title file |

---

## Contact

* [Scott McLean](mailto:smclean@databankimx.com)
* [Dev Team](mailto:development@databankimx.com)
