## Reading files

Reading a file mirrors writing one. You open the file with an `std::ifstream`, which stands for "input file stream", and read from it with the same functions you'd use on `std::cin`. The main difference is that a file has an end, and the loop that reads it has to notice when it reaches that end.

Here's the program for this step, in `src/main.cpp`:

```cpp
std::ifstream in("data/notes.txt");
if (!in) {
    std::cout << "Could not open data/notes.txt\n";
    return 1;
}

std::string line;
int count = 0;
while (std::getline(in, line)) {
    count++;
    std::cout << count << ": " << line << "\n";
}
```

Press **Run**. The output is:

```
1: First note: buy bread.
2: Second note: call the dentist.
3: Third note: finish the report.
Lines read: 3
```

The file has three lines, and the loop reads each one into `line`. `std::getline` reads up to the end of a line, and drops the newline at the end. When it has no line left to read, it returns false, and the loop stops. That's the same pattern as the `while` loops from the loops chapter: the loop runs while the condition is true, and the condition here is "a line was read".

### Why the check matters

The `if (!in)` test works just as the write-side check did. A missing file, or one you aren't allowed to read, gives a stream that didn't open. Reading from it gives nothing, and the loop wouldn't run at all. Without the check, the program would print `Lines read: 0`, which looks like an empty file rather than a missing one.

### Reading words instead of lines

`getline` reads whole lines. To read a file one whitespace-separated word at a time, use `>>`, just as you did with `cin`:

```cpp
std::string word;
while (in >> word) {
    // word holds one word at a time
}
```

The loop stops at the end of the file, just as it did with `getline`. Each `>>` skips spaces and newlines, so the loop sees every word whatever the line breaks look like. Use `getline` when the line structure matters, and `>>` when it doesn't.

---

### Quiz

*These questions are written for this course.*

````quiz
What does `std::getline(in, line)` return when the file has no more lines?
○ An empty string.
→ Not quite. It doesn't store anything new in line, and it reports the failure instead.
◉ false, so the while loop stops.
→ Yes. A read that finds no line returns false, which ends the loop.
○ A newline character.
→ Not quite. The newline is dropped, and there's nothing left to return.
````

````quiz
Why does the program check `if (!in)` before reading?
○ Because reading from a file always fails the first time.
→ Not quite. Reading works when the file opens.
◉ Because a missing file would make the loop silently read nothing, which looks like an empty file.
→ Yes. The check tells a missing file apart from an empty one.
○ Because the check moves the reading position to the start.
→ Not quite. Checking the stream doesn't move anything in the file.
````

---

### Try it in the runner

Change the file name to `data/missing.txt`, and press **Run**. The program reports that it couldn't open the file, and stops. Change the name back before you continue.

Then replace `getline` with `>>` and the word loop from the lesson, counting words instead of lines. Predict the count for the three notes before you run it. The notes contain 4, 5, and 5 words, so the total is 14. Each word is counted with its punctuation attached, so `note:` is one word.

---

Reading and writing use the same stream ideas in opposite directions. The next step puts them together with a problem that catches many programmers out: what happens when a file is written over, and the new text is shorter than the old.
