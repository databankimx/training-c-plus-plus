# Docs

This folder holds reference material that isn't part of the build. The lesson runner and the course's lessons don't read anything here.

## spike-archive

The early experiments that decided how the lesson runner is built. The code is kept so the decisions can be checked later.

### webview2

The first test of hosting a web page in a native g++ program. It opens a window, shows a page, and passes a message each way. The runner's window code grew from this program, but the runner now lives in `lesson-runner\host\app.cpp`, and nothing builds from this folder.

The SDK fetch script moved to `resources\vendor\webview2\fetch-webview2.ps1`, and the SDK itself to `resources\vendor\webview2\sdk`.

### diagnostics

Three small programs that answered questions about the MinGW toolchain, with a script that runs them:

- **`std::stacktrace`** works with `-g` and `-lstdc++exp`. The runner's Backtrace option uses these flags.
- **UndefinedBehaviorSanitizer and AddressSanitizer** can't be used with MSYS2's UCRT64 toolchain. The sanitizer runtime libraries aren't packaged for it, so `pacman` finds nothing to install. The runner doesn't offer a sanitizer option for that reason.

Run `run-diagnostics.ps1` again if the toolchain changes, to see whether the answers have changed.

## Generated files

Build folders in this archive are output from earlier runs, not source. Delete them rather than keep them. The `.gitignore` already excludes them from git.
