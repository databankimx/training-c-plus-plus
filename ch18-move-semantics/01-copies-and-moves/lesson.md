## Copies and moves

Copying an object makes a second, independent object, and for a large object that can be expensive. A string of a million characters has to be duplicated. Often the source is about to be thrown away anyway, so the copy is wasted work. Moving is the alternative: the new object takes over the source's contents, and the source is left empty or in some other valid state.

C++ gives each class two special constructors for this. The copy constructor makes a copy, and the move constructor takes the contents from another object. The class in this step prints a message from each one, so you can see which runs.

Here's the class from `src/main.cpp`:

```cpp
class Buffer {
public:
    Buffer(const Buffer& other) {
        data = other.data;
        std::cout << "Copy " << data << "\n";
    }

    Buffer(Buffer&& other) {
        data = std::move(other.data);
        std::cout << "Move " << data << "\n";
    }

    ~Buffer() {
        std::cout << "Destroy " << data << "\n";
    }

private:
    std::string data;
};
```

The copy constructor's parameter is `const Buffer&`, a reference that promises not to change the source. The move constructor's parameter is `Buffer&&`, an rvalue reference. The two ampersands mark a reference that can bind to an object about to be discarded, such as a temporary, or one the caller has explicitly allowed the program to move from. The rvalue reference is what makes the move possible.

### std::move

The function `std::move` doesn't move anything. It turns its argument into an rvalue, which lets the move constructor run. The name is misleading, and the lesson is that `std::move` is a request, not an action. The actual move happens in the constructor or assignment that receives the rvalue.

The program uses it like this:

```cpp
Buffer c = std::move(a);
```

Press **Run**. The output is:

```
Construct alpha
Copy alpha
Move alpha
All three objects are still valid to use.
Destroy alpha
Destroy alpha
Destroy 
```

The copy `b` gets its own text, so `a` keeps "alpha". The move `c` takes the text from `a`, so `a` is left empty. The last line is `a`, destroyed at the end of `main` with no text, since its contents have been moved away. That's the moved-from state: valid to destroy and to assign to, but holding nothing in particular.

Objects are destroyed in reverse order of creation, which is why `c` prints before `b`, and `a` prints last.

### A moved-from object is valid

The standard says a moved-from object is in a valid but unspecified state. For a `std::string`, in practice it's empty, but a program shouldn't rely on that. The safe ways to use a moved-from object are to assign a new value to it, or to let it be destroyed. Reading its value, as if the move hadn't happened, is a bug.

---

### Quiz

*These questions are written for this course.*

````quiz
What does `std::move` do to its argument?
○ It copies the argument into a new object.
→ Not quite. std::move doesn't copy anything.
◉ It turns the argument into an rvalue, so that a move constructor or assignment can run.
→ Yes. std::move permits a move, and the move itself is done by the receiving constructor or assignment.
○ It deletes the argument.
→ Not quite. The argument is still a valid object, and it's destroyed later in the normal way.
````

````quiz
After `Buffer c = std::move(a);`, what is the safe thing to do with `a`?
○ Read its text, to check the move worked.
→ Not quite. Reading a moved-from object relies on an unspecified state, which is a bug.
◉ Assign a new value to it, or let it be destroyed.
→ Yes. Those are the valid uses of a moved-from object.
○ Copy it, since the copy will contain the original text.
→ Not quite. The original text was moved away, so the copy would not contain it.
````

---

### Try it in the runner

Add `Buffer d = std::move(c);` before the message, and predict the output before you press **Run**. It prints `Move alpha`, since `c` gives its text to `d`. Then predict the destruction messages at the end: `d` is destroyed first, printing `Destroy alpha`, then `c` prints `Destroy` with no text, then `b` prints `Destroy alpha`, and `a` prints `Destroy` with no text.

---

A copy duplicates an object's contents, and a move transfers them. `std::move` only makes the transfer possible, and the moved-from object must not be used for its old value. The next step applies the idea to ownership, where the transfer is the only way to hand an object to someone else.
