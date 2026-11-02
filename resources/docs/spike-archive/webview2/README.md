# WebView2 spike

This is the test that decides whether the C++ lesson runner can use a web front end. It's a small g++ program that opens a window, shows a web page inside it, and passes a couple of messages back and forth. If that works, the runner can reuse the Rust runner's HTML, CSS, and JavaScript. If it doesn't, we need to find out why before we build anything bigger.

It's deliberately dull. No lessons, no runner, just proof that the pieces connect.

## What you need

- **g++ 14 or later**, from MSYS2 UCRT64 (`mingw-w64-ucrt-x86_64-gcc`). Check with `g++ --version`.
- **The WebView2 Runtime.** Windows 11 has it already. On Windows 10 it's usually there too. If it's missing, the fetch script tells you where to get it.
- **Internet access** for the fetch step. The SDK is a NuGet download, about a few megabytes.

## Steps

Open the MSYS2 UCRT64 shell, or a PowerShell window with g++ on the PATH. From this folder:

```pwsh
powershell -ExecutionPolicy Bypass -File .\fetch-webview2.ps1
powershell -ExecutionPolicy Bypass -File .\build.ps1
.\build\webview2-spike.exe
```

The fetch script finds the newest stable WebView2 SDK on NuGet, and unpacks it into `sdk\`. The build script checks your g++ version, compiles `src\main.cpp`, and copies `WebView2Loader.dll` next to the program.

## What success looks like

A window opens, titled "WebView2 spike", and shows a page with a heading and a button.

1. The status line first says "Waiting for the C++ side...", and then changes to **"C++ received: page loaded"**. That's the page talking to C++, and C++ talking back.
2. Click **Send ping**. The status line changes to **"C++ received: ping"**.
3. Close the window. The program exits without an error box.

If you see both replies, the spike has passed, and we can build the runner on this foundation.

## What a failure looks like, and what to send me

Most failures will be one of these:

- **The build fails with errors from `WebView2.h`.** This is the risk I can't rule out from here. The header was written for Microsoft's compiler, and g++ might trip over some of it. Send me the first error, including the line number. It's usually a small fix, but I need the exact text.
- **The build fails with "undefined reference" errors.** Usually a missing library. Send the full message.
- **A message box says WebView2 couldn't start.** The Runtime is missing or damaged. Install it from the Evergreen Bootstrapper, then try again.
- **The window opens, but the page is blank.** Send me what the message box says, if anything. A blank page usually means the page didn't load, and the error box would have said why.
- **The window opens, and nothing else happens.** The message round trip failed. Tell me whether the status line changed at all, since that tells us which direction broke.

Whatever happens, send me the exact text of any error, along with your `g++ --version` output. That's usually enough for me to work out the next step.

## Notes on the code

`src\main.cpp` does three jobs. It loads `WebView2Loader.dll` at runtime, which avoids linking against Microsoft's compiled libraries. It implements the COM callbacks by hand, which is a bit verbose, but keeps the code readable for a student. And it keeps all the WebView2 calls in one `Host` class, so the runner can build on it later without a rewrite.

The page itself is a raw string at the top of `main.cpp`. You can change it and rebuild to try your own messages.
