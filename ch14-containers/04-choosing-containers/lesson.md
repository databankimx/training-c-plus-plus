## Choosing a container

The last three steps introduced three containers that look similar on the surface: arrays, vectors, and maps. Each one suits a different job. This step puts them side by side, and shows how a program often uses more than one.

Here's the program for this step, in `src/main.cpp`. It keeps the names in a vector, and builds a map from each name to its length:

```cpp
std::vector<std::string> names = {"Ada", "Grace", "Alan"};

std::map<std::string, int> lengths;
for (const std::string& name : names) {
    lengths[name] = static_cast<int>(name.size());
}
```

Press **Run**. The output is:

```
Names: 3
Ada: 3
Alan: 4
Grace: 5
```

The vector holds the names in the order they were given. The map holds the lengths, looked up by name, and prints them sorted. Neither container is wrong for its job: the vector keeps order, and the map answers lookups.

### A comparison

| Container | Size | Finds a value by | Keeps order | Use it when |
|---|---|---|---|---|
| Array | Fixed when declared | Index | The order it was written in | The size is known and never changes |
| `std::vector` | Grows with `push_back` | Index | The order it was added in | You have a list, and its size isn't known in advance |
| `std::map` | Grows with insertion | Key | Sorted by key | You look values up by a name or other key |
| `std::unordered_map` | Grows with insertion | Key | No order is guaranteed | Lookups dominate, and the order of the entries doesn't matter |

### What each one costs

The table says what each container is for. Its cost is the other half of the choice, and the figures here are the outline. The efficiency chapter measures them with operation counts.

* **An array** lives in one fixed block, so reading by index is immediate and nothing is allocated after it's declared.
* **A vector** also lives in one block, so reading by index is just as fast. Adding to the end is cheap on average, as the vectors step explained. Inserting or removing in the middle means moving the elements after that point, which takes time in proportion to how many there are.
* **A map** allocates each entry separately, so the entries are spread through memory. A lookup or insertion compares the key against a few entries, and the number compared grows with the logarithm of the map's size. Spreading the entries out also means more cache misses than a vector.
* **An unordered map** stores its entries in buckets, chosen by a hash of the key. A lookup usually goes straight to the right bucket, so the average cost stays about the same as the map grows. The table itself takes memory, and when many keys land in the same bucket, a lookup can slow down.

The default is a vector. It's the simplest container that grows, and it's the one most code reaches for first. Move to a map when the main question is "what is the value for this key?", and use an array only when the size is fixed and small. If the key lookups are the bottleneck and the order doesn't matter, an unordered map is the faster choice, as the previous step explained.

### Several containers together

Real programs often combine containers, as this one does. The vector keeps the names in input order, and the map answers questions about them. Each container does the job it's best at, and the program is clearer than one that forces a single container to do both.

### What the containers share

The three containers are used in the same way where it matters. Each has a size, each supports the range-based `for`, and each can hold any type you choose, including your own structures and classes. You'll meet that last point again in the templates chapter, where a container of your own type is written once for all types.

---

### Quiz

*These questions are written for this course.*

````quiz
Which container would you choose to store a list of exam scores, whose count is not known until the program runs?
○ An array, since it's the simplest.
→ Not quite. An array's size is fixed when it's declared, and this count isn't known in advance.
◉ A std::vector, since it grows as values are added.
→ Yes. A vector keeps the order and grows to fit the data.
○ A std::map, since it stores more information.
→ Not quite. A map is for lookups by key, and a list of scores doesn't need keys.
````

````quiz
Which container would you choose to find a student's grade from the student's name?
○ A std::vector of grades, searched from the start.
→ Not quite. That would work, but it's a search through the whole list, and the map is designed for this.
◉ A std::map from name to grade.
→ Yes. The map looks up the value for a key directly.
○ An array of names, with the grade at the same index.
→ Not quite. That relies on keeping two lists in step, which is easy to get wrong.
````

---

### Try it in the runner

Add `"Ada"` a second time to the vector, and press **Run**. Predict how many entries the map holds afterwards. It still holds three, since the map is keyed by name, and the second "Ada" writes to the same entry.

Then add a line that prints `names.size()` after the loop, and predict the output. It's 4, since the vector keeps every name, even repeats. The two containers disagree on purpose: the vector records the input, and the map records the unique names.

---

A vector keeps a list in order, a map finds values by key, and an array is for a fixed set. Choosing one is a question about the main job the data has to do. Chapter 14 covers the containers, and the homework applies them to two small programs.
