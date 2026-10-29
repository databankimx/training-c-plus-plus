## Recursion

A function that calls itself is called recursive. It sounds like a trick, but many problems have this shape: a task that's made of smaller copies of the same task. Folders are a good example. A folder contains files and other folders, and each of those folders contains files and folders in turn. To list everything under a folder, you list its entries, and for each subfolder you do the same job again, on a smaller part of the tree.

Here's the program for this step, in `src/main.cpp`. The `sample` folder beside it holds a small tree, and the program lists it:

```cpp
void listFolder(std::filesystem::path folder, int depth) {
    for (std::filesystem::directory_entry entry : std::filesystem::directory_iterator(folder)) {
        std::cout << std::string(depth * 2, ' ') << entry.path().filename().string() << "\n";
        if (entry.is_directory()) {
            listFolder(entry.path(), depth + 1);
        }
    }
}
```

Press **Run**. The output lists every entry, with each level indented under its folder. One possible result is:

```
readme.txt
notes.txt
photos
  holiday.txt
  beach
    wave.txt
music
  song.txt
```

The order of the entries depends on the file system, not on the names, so your listing may come in a different order. The contents are the same.

### What the recursion does

The function does one job: it lists the entries of one folder. For each entry, it prints the name. If the entry is a folder, the function calls itself on that folder, with `depth` one larger, to list what's inside. The call handles a smaller tree, and it finishes before the loop moves on to the next entry.

The recursion stops because the tree is finite. An ordinary file doesn't call the function, so it's the end of that branch. A folder with no subfolders gives a loop that calls nothing more. Every branch eventually reaches files, and the calls unwind back to the top.

### The depth parameter

The `depth` argument doesn't affect what gets listed. It only controls the indentation, so the output shows which folder each entry belongs to. Each call passes `depth + 1`, so entries inside a folder are indented one more step than the folder. The value is a counter that travels down the recursion, and it's the same idea as the parameters from earlier in the chapter.

### The library behind it

`std::filesystem`, from the `<filesystem>` header, is the standard library's way to work with files and folders. A `std::filesystem::path` holds a location, and `std::filesystem::directory_iterator` gives the entries in a folder. A range-based `for` loop works on it, just as it does on an array, so the loop visits each entry in turn. Each entry knows whether it's a folder, through `is_directory()`.

Recursion and loops often work together like this. The loop handles the entries at one level, and the function call handles each level below.

### A warning about loops

A folder can contain a link that points back to an ancestor folder, and then the recursion never reaches a file or an empty folder. The program would keep going until something fails. Real tools track which folders they've visited, to avoid this. The sample tree has no such links, so this program is safe, but keep the risk in mind for any recursion over data you don't control.

---

### Quiz

*These questions are written for this course.*

````quiz
What stops the recursion in `listFolder`?
○ A counter that reaches a fixed limit.
→ Not quite. The depth grows as the tree goes deeper, but nothing stops at a fixed limit.
◉ The tree is finite, so every branch eventually reaches files, which don't call the function.
→ Yes. Each branch ends at a file or an empty folder.
○ The function returns a value to say it's finished.
→ Not quite. listFolder returns nothing, and it stops because the tree runs out.
````

````quiz
What does the `depth` parameter change in the output?
○ Which entries are listed.
→ Not quite. Every entry is listed whatever the depth.
◉ How far each entry is indented under its folder.
→ Yes. depth only controls the indentation.
○ The order in which the files appear.
→ Not quite. The file system decides the order, not depth.
````

---

### Try it in the runner

Rename one file in `sample`, such as `notes.txt` to `trip.txt`, and press **Run**. The listing shows the new name in the same place. Then move `wave.txt` out of `beach` and into `music`, and predict where it appears in the listing before you run.

Then consider what would happen if `sample` contained a link back to `sample` itself. Describe what the recursion would do, and why the program would never finish. You don't need to build that case, since the lesson's warning explains it.

---

Recursion is a function that handles one level of a problem, and calls itself for the smaller problems inside it. Some recursive solutions are correct but wasteful, since they repeat work they've already done. That's a question of cost, and the summary and homework look at it when they come back to the chapter's examples.
