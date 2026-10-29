## Declaring arrays

So far, each value has had its own variable. That works for a handful of values, but a program that handles a list of twelve temperatures or a week of sales figures would need twelve names. An array stores many values of the same type under one name, and you pick the value you want by its position.

Here's the program for this step, in `src/main.cpp`:

```cpp
std::string cars[4] = {"Volvo", "BMW", "Ford", "Mazda"};
int nums[3] = {10, 20, 30};

std::cout << cars[0] << "\n";
std::cout << nums[2] << "\n";
```

Press **Run**. The output begins:

```
Volvo
30
```

Read the declaration as "cars is an array of four strings". The type comes first, then the name, then the number of elements in square brackets. The braces hold the starting values, in order. Every element in an array has the same type, so `cars` holds only strings and `nums` only integers.

### Indexing from zero

To get one element, write the array's name followed by its position in square brackets. That position is called the index, and the first element is at index 0, not 1. So `cars[0]` is "Volvo", and `nums[2]` is the third element, 30.

The index starts at zero for the same reason positions in a string did in Chapter 2. It's the distance from the start of the array, so the first element is zero steps away. Once you've got used to it, it stops feeling strange.

### Changing elements

You can read an element and write to it, in the same way you'd use a variable:

```cpp
cars[0] = "Opel";
nums[2] += 5;
```

Now `cars[0]` holds "Opel", and `nums[2]` holds 35. The `+=` works here as it does on any `int` variable, since `nums[2]` is an `int` that happens to have a position.

### Going past the end

An array of four elements has valid indexes 0, 1, 2, and 3. Asking for index 4 is outside the array, and C++ doesn't check. Nothing stops you, and the result is undefined. The program might print a garbage value, crash, or seem to work and fail later, in a different part of the code.

This is one of the most common bugs in C++ code, and the compiler usually can't catch it when the index is calculated at run time. The "Try" in this step shows it.

---

### Quiz

*These questions are written for this course.*

````quiz
What is the index of the third element in `int nums[3]`?
○ 3
→ Not quite. That's past the end of a three-element array.
◉ 2
→ Yes. Indexes start at 0, so the third element is at index 2.
○ 1
→ Not quite. That's the second element.
````

````quiz
What is `cars[0]` after `cars[0] = "Opel";`?
○ "Volvo"
→ Not quite. The assignment replaced the value at index 0.
◉ "Opel"
→ Yes. Assignment through an index works just like assignment to a variable.
○ An error, because arrays can't be changed.
→ Not quite. Array elements can be changed, unless the array is declared const.
````

---

### Try it in the runner

Add a line that sets `int index = 4;`, then prints `cars[index]`, and press **Run** only after you've made a prediction. The array has four elements, so index 4 doesn't exist. The compiler doesn't check the index, because it isn't known until the program runs, so the program builds and runs anyway. The result is undefined. Depending on what sits in memory after the array, you might see garbage, a crash, or nothing unusual at all. That's the point of the exercise: the program looks fine, and it isn't.

---

An array gives one name to a whole list of values, and an index picks out one of them. The next step covers how to fill an array when you create it, and how to find out how long it is.
