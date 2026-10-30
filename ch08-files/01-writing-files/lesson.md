## Writing files

Every program so far has written to the screen and read from the keyboard. A file is a third place for data, and it's the one that outlives the program. The standard library handles files with stream classes from the `<fstream>` header, and writing to one looks a lot like writing to `std::cout`.

Here's the program for this step, in `src/main.cpp`:

```cpp
std::ofstream out("data/greetings.txt");
if (!out) {
    std::cout << "Could not create the file.\n";
    return 1;
}

out << "Hello, file!\n";
out << "Writing to a file works like cout.\n";
out.close();
```

Press **Run**. The program prints one line, `Wrote data/greetings.txt`. The program doesn't print the file's contents. A **View** button appears over the bottom right of the Output pane, named for the file. Press it to open the file in the default application for text files.

### The output stream

`std::ofstream` is the class for writing to a file. Its name stands for "output file stream". You create one with the file's path, and that opens the file for writing. The `<<` operator works just as it does with `std::cout`, so you can send text and numbers to the file in the same way.

The path is relative to the folder the program runs from. The runner runs each step in a copy of its folder, so `data/greetings.txt` refers to the `data` folder inside that copy.

### Checking that the file opened

Opening a file can fail. The folder might not exist, the file might be locked, or you might not have permission to write it. The `if (!out)` check tests whether the stream opened correctly, and returns early if it didn't. Skipping the check means the writes go nowhere, and the program carries on as if they had worked.

### Closing the file

The program calls `out.close()` when it's finished writing. Closing flushes any text still waiting in the stream's buffer, and releases the file so other programs can use it. A file that isn't closed may not contain all of its text, and that's a bug that's hard to see.

There's a safer habit. When an `ofstream` goes out of scope, as it does when its enclosing block ends, the file closes automatically. You'll see this in the third step of this chapter, and it's the first example of a pattern the course returns to with smart pointers.

---

### Quiz

*These questions are written for this course.*

````quiz
Which header provides the file stream classes?
○ <iostream>
→ Not quite. <iostream> provides cout and cin, not file streams.
◉ <fstream>
→ Yes. <fstream> provides ofstream, ifstream, and fstream.
○ <filesystem>
→ Not quite. <filesystem> works with paths and folders, but writing text uses <fstream>.
````

````quiz
Why does the program check `if (!out)` after creating the stream?
○ Because out has to be checked before any text can be written.
→ Not quite. The check is about whether the file opened, not about the text.
◉ Because the file might not open, and writes to a stream that didn't open go nowhere.
→ Yes. The check catches a failed open, so the program can report it.
○ Because ofstream objects are always empty.
→ Not quite. The check tests the stream's state, which can be bad after a failed open.
````

---

### Try it in the runner

Change the path to `data/missing/greetings.txt`, where `missing` is a folder that doesn't exist, and press **Run**. The program reports that it couldn't create the file, and returns early. Change the path back before you continue.

Then remove the `out.close();` line, and run again. The program still works here, because the file closes when `out` goes out of scope at the end of `main`. Put the line back, since closing explicitly makes the point where the file is finished easy to see.

---

Writing a file is an ordinary stream operation with a path attached. The next step reads one back, and shows how the same class idea works in the other direction.
