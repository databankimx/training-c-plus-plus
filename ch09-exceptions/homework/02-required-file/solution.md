## Solution: Required file

The function checks the stream straight after opening it, and throws if the open failed. It doesn't read anything from a stream that didn't open, so the caller never sees a silent empty result. The exception carries the file name, which is the detail someone reading the message needs.

`main` puts the call in a `try` block, and catches the exception by `const` reference, so `what()` gives the message. The catch is the only place that decides what the user sees. The function reports the problem, and `main` decides how to present it.

The message is built with the file name joined onto the text, so `could not open data/missing.txt` names the file that failed, and nothing else.

For the first extension, an empty name is a mistake in the code that calls `printFile`, so it's a logic error, and `std::invalid_argument` fits. A missing file is a problem with the environment, which is a runtime error. The second extension needs its own `try` block around each call, so that one failure doesn't stop the next file from being tried.
