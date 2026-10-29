# DataBank IMX - C++ Developer Training

## License and Support

This repository is provided under the [MIT License](LICENSE). You are free to use, copy, modify, merge, publish, distribute, sublicense, and/or sell the materials in this repository, subject to the terms of that license.

This repository is provided for training and reference purposes only. DataBank IMX does not provide warranties, guarantees, maintenance, troubleshooting, implementation assistance, or technical support for this code or its use. Use it in any way permitted by the MIT License, but you are responsible for evaluating, adapting, testing, and supporting any use of it in your own environment.

---

## What is this repository for?

- C++ developer training curriculum for DataBank IMX, covering the language from first programs through the standard library, with a focus on reading and converting existing C++ code
- Chapter-by-chapter lessons, with code you can edit and run, and short quizzes
- A final project: a calculator built in stages, with a core track and a bonus track, each with a worked example
- A desktop lesson runner, built with C++, that lets you read lessons, edit and run each step, and run its tests

---

## About

- **Author:** [Scott McLean](mailto:smclean@databankimx.com)
- **Purpose:** Internal developer training curriculum for DataBank IMX

---

## DataBank Responsibilities for Custom Code

All DataBank employees, including those working with AI-assisted tools, are bound by the [Development Rules of Engagement](development-rules-of-engagement.md). That document defines the rules for quoting, approving, developing, reviewing, scanning, storing, and delivering custom code for client work.

Key obligations that apply to everyone on every custom code engagement:

- **You own the code you deliver.** This applies equally to hand-written code, AI-assisted code, and AI-generated code.
- **Code must be reviewed before delivery.** Review must confirm that the code works, meets DataBank standards, and is maintainable, and that the developer understands it well enough to explain, debug, and maintain it.
- **Code must be in source control before delivery.** All custom code must be committed to the appropriate DataBank GitHub Enterprise repository before it is delivered to a client.
- **CI scanning must pass before delivery.** Required checks are the standards policy scan, SonarQube, and Snyk.
- **All third-party dependencies must be license-vetted.** The license must permit closed-source commercial use. Copyleft or unclear licensing must be escalated before use.
- **Only approved AI tools may be used.** Use only IT-approved tools through company accounts.
- **Custom code is billable work.** Code must be tied to an approved quote or engagement before commitment or delivery.

See the [Development Rules of Engagement](development-rules-of-engagement.md) for the full policy.

---

## Textbook reference

The lessons follow two references. Both are free, and both are linked from the lessons that use them.

- [Learn C++](https://www.learncpp.com/), by Alex Allain. A complete, free course, organized in the order the lessons follow.
- *A Tour of C++*, third edition, by Bjarne Stroustrup (Addison-Wesley). A short guide to the language, written by its designer, used in the modern-features chapters.

Lessons quote only the short examples they need from these references, and explain the rest in their own words. Before the course is published more widely, the reuse terms of each reference are confirmed.

---

## Setup and requirements

- **Windows 10 or 11**, with the WebView2 runtime (included with Windows 11)
- **MSYS2**, with the UCRT64 toolchain: g++ 14 or later, CMake, and Ninja
- **VS Code** with the C/C++ extension (recommended), or any editor you prefer

See [QUICKSTART.md](QUICKSTART.md) for a step-by-step guide.

### Quick start

From the repository root, in PowerShell:

```pwsh
powershell -ExecutionPolicy Bypass -File .\setup.ps1 -InstallMissing
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
| highlight | Lesson runner (web folder) | Syntax coloring in the Source and Lesson panes | Written for this course |
| ImageMagick, librsvg | Setup only | Makes the runner's icon from the SVG logo. Not linked into any program | Apache 2.0 and LGPL-2.1, used as separate tools |

The GCC runtime exception and the Graphviz license should be reviewed under section 12 of the Development Rules of Engagement before the course leaves the company. The runner itself links only the MIT, BSD, Apache, and Microsoft-licensed components above.

### VS Code

Install the **C/C++** extension (publisher `Microsoft`). It checks your code as you type, and offers completion and navigation.

---

## Running the training

### Lesson Runner

The lesson runner is a desktop window, built with C++ and WebView2. It lets you browse chapters, read lessons, edit and run each step, and run its tests. Setup is in [QUICKSTART.md](QUICKSTART.md).

#### Finding lessons

The chapter list on the left shows each chapter, such as *Ch01 · Basics*. Click a chapter to show its steps, then click a step to open it.

- Chapters are listed in order. The final project comes after the numbered chapters.
- Each step is one folder. A step with a `CMakeLists.txt` has code you can run.
- Homework appears under its chapter, in its own list.

#### Reading and running a step

- The **Lesson** tab shows the step's lesson, with quizzes.
- The **Source** tab shows the step's `src/main.cpp`. It's an editor. Edits are kept in the runner until you click **Reset**, and nothing is written to the repository.
- Press **Run** (or F5) to build and run the step. The build status lines appear in the Output pane, followed by the program's output.
- Press **Test** to build the step and run its tests, for steps that have them.
- If a program asks for input, type in the input box under the Output pane, then press Enter or click **Go**.
- Press **Escape**, or click **Stop**, to stop a run. The Run button becomes Stop while a program runs.
- The **Backtrace** checkbox builds with stack-trace support, so a `std::stacktrace` in a step shows function names.

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

- **The window doesn't open:** check that the toolchain is in `C:\msys64\ucrt64\bin`, and run `setup.ps1` again.
- **Run says it could not start a build tool:** the MSYS2 toolchain isn't installed, or isn't in that folder.
- **A step says it didn't build a program:** the step's `CMakeLists.txt` should build an executable called `program`.
- **The first build is slow:** normal. Later builds are faster.

The runner's source code is in `lesson-runner/host` (the C++ back end) and `lesson-runner/web` (the page).

### Running lessons directly

Each step with code is a CMake project. From a terminal, in the step's folder:

```pwsh
cmake -S . -B build -G Ninja -DCMAKE_CXX_COMPILER=g++
cmake --build build
.\build\program.exe
```

---

## Repository structure

```
training-cpp/
|- ch01-getting-started/         - Chapter 1: setup, the first programs, and the summary
|- ch02-variables-and-input/     - Chapter 2: variables, arithmetic, strings, and input
|- ch03-decisions/               - Chapter 3: booleans, logical operators, if statements, and switch
|- ch04-arrays/                  - Chapter 4: declaring, initializing, and multidimensional arrays
|- ch05-references-and-pointers/ - Chapter 5: references, pointers, and pointers with arrays
|- ch06-loops/                   - Chapter 6: loops, break and continue, and a Battleship game
|- ch07-functions/               - Chapter 7: functions, parameters, return values, arrays, reference parameters, and recursion
|- ...                           - Further chapters, as they are written
|- lesson-runner/                - The desktop lesson runner
|  |- host/                      - C++ back end: window, router, runner, discovery
|  |- web/                       - The page: HTML, CSS, JavaScript, and the vendored libraries
|- resources/                    - Setup documents, snippets, vendored downloads, and the runner's test steps
|- setup.ps1                     - Prepares everything the runner needs
|- QUICKSTART.md                 - Step-by-step setup guide
|- AUTHORING.md                  - How to write and check lessons
```

Each chapter folder holds its sections, and each section holds its steps. A step is a folder with a `lesson.md`, and a `CMakeLists.txt` if it has code. Steps appear in the order of their names, so the number prefix keeps them in order.

### Course outline (in progress)

| Part | Chapters | Status |
|---|---|---|
| I - Basics | Getting started, variables and input, decisions, arrays, references and pointers, loops, functions, structures, classes, inheritance and polymorphism, headers and multiple files | In progress. Chapters 1 to 7 are written. The remaining chapters are planned, and the earlier tutorial's examples will be converted into them |
| II - Standard library | Files, exceptions, containers, iterators and algorithms, RAII and smart pointers, move semantics, templates, lambdas, testing, concurrency | Planned |
| III - Beyond the book | Build systems, debugging and sanitizers, modern features, projects | Planned |
| Final project | A calculator, in two tracks: a core and bonus items | Planned |

The outline is a plan and may change as the lessons are written.

---

## Authorship note

This training curriculum was developed for internal use at DataBank. As with the other training repositories, I used generative AI in places for code review, cleanup, and turning rough notes into readable documentation.

~ Scott McLean, 2026

---

## Version history

| Date | Changes |
|---|---|
| 10/29/2026 | Initial version: the lesson runner, the setup and quickstart guides, the authoring guide, a placeholder chapter for checking the runner, and the calculator final-project homework |

---

## Contact

- [Scott McLean](mailto:smclean@databankimx.com)
- [Dev Team](mailto:development@databankimx.com)
