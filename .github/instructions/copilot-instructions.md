---
applyTo: "**/*"
---

# GitHub Copilot Instructions - DataBank Development Standards

## Purpose
This file defines how GitHub Copilot should generate code for DataBank IMX development teams.
All generated code must align with internal standards for quality, maintainability, security, and consistency.

## Scope
This repository is a **C++ training repository** (C++23, built with CMake, g++, and Ninja on MSYS2 UCRT64 for Windows). Follow the **Common Standards** section and the **C++ Project Instructions** section for all code generation in this repository.

---

## Common Standards

### General Principles
- Prioritize **readability, maintainability, and clarity** over brevity.
- Follow **DataBank coding standards** at all times.
- Assume code will be **reviewed, tested, and deployed to client environments**.
- Avoid unsafe, experimental, or non-production-ready patterns.
- Do not introduce unnecessary dependencies or frameworks.
- Third-party packages **must** have licenses that allow closed-source commercial use.
- Prefer existing project patterns over introducing new architectural or library choices.

### Architecture and Design
- Prefer clear separation of concerns.
- Avoid tightly coupled designs.
- Design for reuse and extensibility.
- Keep controllers, endpoints, and entry points thin; place business logic in services or domain components.
- Match the structure and conventions already used by the repository unless the user explicitly requests a redesign.

### Error Handling and Security
- Validate all inputs.
- Avoid exposing sensitive information in exceptions, logs, API responses, or console output.
- Follow least-privilege principles.
- Do not generate insecure defaults, hardcoded secrets, or bypass validation/authentication/authorization checks.
- Exception and error messages must be clear, concise, grammatically correct, and end with a period.

### Comments and Documentation
- Write comments only when necessary.
- Use clear, concise US-English.
- Document complex logic, non-obvious decisions, and important operational behavior.
- Avoid comments that merely restate the code.

### Source Control and Workflow
- All code must be tracked in source control.
- Commit early and often.
- Use meaningful commit messages.
- Link commits to tasks, issues, bugs, or enhancements where appropriate.
- Use branches and pull requests for review; do not commit directly to protected mainline branches.

### Code Reviews and Quality Gates
- All code must be reviewed before merge or delivery.
- Address correctness, readability, performance, security, and maintainability.
- Where applicable, code must pass SonarQube or other required quality gates before merge.

### Testing and QA Expectations
- Follow a **test-driven mindset** where practical.
- Ensure new code is testable.
- Include unit tests and integration tests where appropriate.
- Consider edge cases, invalid inputs, failure scenarios, and regression risk.

### Prohibited Practices
- Do NOT generate hardcoded credentials, secrets, tokens, or connection strings.
- Do NOT introduce unapproved third-party libraries.
- Do NOT expose internal implementation details unnecessarily.
- Do NOT produce code that violates DataBank IP, security, or delivery policies.

---

## C++ Project Instructions

### General Style

- Write clear, portable modern C++ targeting the standard set in each lesson's `CMakeLists.txt` (C++23 unless stated otherwise).
- Prefer explicit, maintainable code over compact or clever code.
- Use descriptive names for functions, variables, types, and parameters.
- Match the repository's existing layout, naming, and brace/indent style.
- Compile cleanly with warnings enabled (`-Wall -Wextra -Wpedantic`) and fix warnings rather than suppressing them.

### Structure

- Keep functions small and single-purpose.
- Put declarations in headers (`.hpp` or `.h`) with include guards or `#pragma once`, and implementations in `.cpp` files.
- Use anonymous namespaces or `static` for names that are private to a file.
- Keep `main` thin; place logic in separate functions or classes.
- Reuse existing helpers and patterns before introducing new ones.

### Memory and Safety

- Follow RAII. Use `std::unique_ptr`, `std::shared_ptr`, and standard containers instead of raw `new`/`delete` and `malloc`/`free`.
- Make ownership clear in types and names. A raw pointer or reference is a non-owning view.
- Prefer `std::string`, `std::string_view`, `std::vector`, `std::array`, and `std::span` over C strings and raw arrays.
- Never use unbounded C functions such as `gets`, `strcpy`, `strcat`, or `sprintf`.
- Validate input, container indexes, and pointer arguments before use. Prefer `at()` where bounds are not otherwise guaranteed.
- Avoid undefined behavior: uninitialized reads, out-of-bounds access, signed overflow, dangling references, use after move, use after free.
- Use `const`, `constexpr`, and `[[nodiscard]]` where appropriate. Prefer `enum class` and `nullptr`.
- Avoid C-style casts. Use `static_cast` and friends.
- Code should run clean under AddressSanitizer and UndefinedBehaviorSanitizer where applicable.

### Error Handling

- Use exceptions, `std::optional`, or `std::expected` consistently with the surrounding code. Do not ignore return values.
- Do not throw from destructors. Release resources through RAII on every error path.
- Keep user-facing error messages clear and safe.

### Logging and Output

- Write errors to `std::cerr` and normal output to `std::cout`.
- Never print secrets, credentials, tokens, or sensitive customer data.

### Documentation

- Add comments when behavior is not obvious. Keep inline comments minimal and purposeful.

### Testing

- Prefer simple, self-contained test programs that use `assert` or small check helpers, built and run through CMake/CTest.
- Do not add third-party test frameworks unless already required by the repository.
- Cover normal flow, invalid input, edge cases, and failure paths.

### Training Repository Notes

- This repository contains training content. Lesson files and homework are teaching material, not production code.
- Vendored third-party code under `resources/vendor/` and `lesson-runner/web/vendor/` is not ours to restyle or harden. Do not modify it.
- The lesson runner (`lesson-runner/`, a C++ host plus a web front end) is the only application code. Hold it to the full standards above.
- Follow the conventions in `AUTHORING.md` when writing or editing lessons.

---

## Copilot Behavior Guidelines

When generating code, Copilot should:
- Follow all applicable rules in this document automatically.
- Prefer existing project patterns over new ones.
- Match surrounding code style closely.
- Avoid speculative implementations.
- Ask for clarification through comments or generated TODO notes only when requirements are genuinely unclear.

---

## Definition of Done

Generated code is acceptable only if it:
- Runs successfully without warnings in the target project context.
- Passes required static analysis and quality gates where applicable.
- Follows the C++ standards in this file.
- Includes appropriate validation, error handling, and safe memory use.
- Is readable, maintainable, and testable.
