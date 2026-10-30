## Destructors and scope

Some work has to be undone. A file has to be closed, a lock has to be released, and memory has to be given back. C++ has a pattern that ties that undoing to the lifetime of an object, so it happens automatically and at the right moment. It's called RAII, which stands for resource acquisition is initialization, and the core of it is the destructor.

You've already used it. An `std::ofstream` opens its file when it's created, and closes it when it goes out of scope. You never called `close` in the later steps of the file chapter, and the file was still closed correctly. This chapter explains how that works and how to write the same kind of class yourself.

Here's the class for this step, from `src/main.cpp`:

```cpp
class Resource {
public:
    Resource(std::string resourceName) {
        name = resourceName;
        std::cout << "Acquire " << name << "\n";
    }

    ~Resource() {
        std::cout << "Release " << name << "\n";
    }

private:
    std::string name;
};
```

The constructor runs when an object is created, and it acquires the resource. Here it prints a message, which stands in for opening a file or taking a lock. The destructor has the class's name with a tilde in front, and it has no parameters and no return value. It runs when the object's life ends, and it releases the resource.

### When the destructor runs

An object's life ends at the closing brace of the scope it was created in. That scope might be a block, a function, or the whole program. The program uses both kinds:

```cpp
{
    Resource second("file B");
    std::cout << "Using file B\n";
}
```

Press **Run**. The output begins:

```
Start
Acquire file B
Using file B
Release file B
```

The destructor for `second` runs at the closing brace of the block, before the next statement. The block is the scope, so the release happens exactly when the work in that scope is finished.

A function works the same way. The `useResource` function creates `first`, and its destructor runs when the function returns:

```
Acquire file A
Using file A
Release file A
End
```

The release comes before `End`, because `first` is destroyed when `useResource` returns, and the program continues after that.

### Why this matters

The release happens on every way out of the scope, not only the normal one. If the function returned early, or a `throw` from the exceptions chapter left it, the destructor would still run. A program that closes files by hand, with a `close` call at the end of each function, can skip that call on an early return and leak the file. An object that closes its own file in its destructor can't skip it.

This is why the file streams from Chapter 8 didn't need `close` to be correct. The stream is an object, its destructor closes the file, and the destructor runs when the stream goes out of scope.

### Order of destruction

When several objects are created in one scope, they're destroyed in the reverse order. The last one created is the first one released. That matches how they were built on top of one another, and it's the order that keeps dependent resources safe.

---

### Quiz

*These questions are written for this course.*

````quiz
When does a local object's destructor run?
○ When the program ends.
→ Not quite. Local objects are destroyed earlier, at the end of their own scope.
◉ When the scope the object was created in ends, including on an early return or a throw.
→ Yes. The destructor runs on every way out of that scope.
○ When the object is first used.
→ Not quite. Its lifetime is set by the scope, not by the first use.
````

````quiz
Why doesn't `std::ofstream` need a `close` call to be correct?
○ Because files close themselves after a few seconds.
→ Not quite. Timing doesn't close the file.
◉ Because its destructor closes the file when the stream goes out of scope.
→ Yes. That's the RAII pattern: the object owns the resource, and its destructor releases it.
○ Because the operating system closes every file at the end of the program.
→ Not quite. The file is closed when the stream goes out of scope, which can happen long before the program ends.
````

---

### Try it in the runner

Add a `Resource` named `file C` in `main`, after `End` is printed, and predict its messages before you press **Run**. It prints `Acquire file C` after `End`, and then `Release file C` as the very last line, when `main` returns.

Then move the `file C` object inside an `if` block that never runs, and predict what happens. Nothing prints for it at all, since the object is never created.

---

RAII ties the release of a resource to the end of the object's life, so cleanup happens on every path. The next step applies the same idea to memory that's allocated on the heap, using `std::unique_ptr`.
