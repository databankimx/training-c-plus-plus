## Overwriting files

The last two steps wrote a file and read one back, and they seemed to work. This step shows a mistake that's easy to make, and that gives wrong results without any error message.

Here's the program for this step, in `src/main.cpp`. It writes a long line, then writes a short line over it:

```cpp
{
    std::ofstream out("data/test.txt");
    out << "This first version of the text is quite long.";
}

std::fstream file("data/test.txt");
file << "Short text.";
file.close();
```

Before you press **Run**, predict the output. The program then reads the file back and prints it. Press **Run** and check your prediction. The output is:

```
Short text.version of the text is quite long.
```

Only the first eleven characters were replaced, and the rest of the original line survived. Nothing reported an error, because nothing went wrong in the sense the stream checks for. The stream did exactly what it was asked to: it wrote the new text at the start of the file, and it didn't clear what came after.

### Why it happens

`std::fstream` opens an existing file for both reading and writing, and it leaves the existing contents in place. Writes start at the beginning of the file, and they overwrite whatever bytes are there. If the new text is shorter than the old, the leftover bytes remain at the end.

The fix is to say, when you open the file, that its old contents should be discarded. The `std::ofstream` class does this by default, because it's only for writing, and its mode clears the file when it opens. You can also ask `std::fstream` to clear the file with the `std::ios::trunc` flag, which the next step's Try shows. Whichever you use, the rule is the same: open for writing only when you intend to replace the whole file.

### The block and closing

The first part of the program, in braces, ends with `out` going out of scope. The file closes at the closing brace, before the program reads it back. That's the same automatic closing the writing step described. Without the braces, `out` would stay open until the end of `main`, and the reading code would see the file before its last text was flushed.

---

### Quiz

*These questions are written for this course.*

````quiz
Why does `std::fstream` leave the rest of the old text in place?
○ Because fstream always appends to the end of the file.
→ Not quite. It writes from the start of the file, not the end.
◉ Because it opens the existing file without clearing it, so only the bytes written are replaced.
→ Yes. Writes overwrite from the start, and anything beyond the new text stays.
○ Because the file is locked while it's open.
→ Not quite. Locking has nothing to do with the leftover text.
````

````quiz
Which way of writing a file replaces its whole contents?
○ std::fstream, with no other options.
→ Not quite. It keeps the existing contents, so leftover text survives.
◉ std::ofstream, which clears the file when it opens.
→ Yes. An ofstream discards the old contents when it opens the file.
○ std::ifstream, which reads the file first.
→ Not quite. ifstream reads, and can't write at all.
````

---

### Try it in the runner

Change `std::fstream` to `std::ofstream`, and predict the output before you press **Run**. The new text replaces the whole file, so the output is `Short text.` and nothing more.

Then go back to `std::fstream`, and add the `std::ios::trunc` flag as a second argument to the constructor: `std::fstream file("data/test.txt", std::ios::out | std::ios::trunc);`. Predict the output. It's `Short text.`, since the flag clears the file when it opens.

---

Writing, reading, and overwriting cover the basics of file access. The summary and homework put them together, and the next chapter adds exceptions, which is the other standard way to report a file that won't open.
