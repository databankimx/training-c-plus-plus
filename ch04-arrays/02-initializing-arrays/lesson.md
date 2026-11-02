## Initializing arrays

The last step set each array element in its braces, which is one way to start an array. C++ offers several more, and you'll use each of them in different situations. This step covers the common ones, and the ways to find out how many elements an array holds.

Here's the program for this step, in `src/main.cpp`. It begins with an array that's only partly filled in:

```cpp
int partial[5] = {7, 8};
std::cout << partial[0] << " " << partial[1] << " " << partial[2] << " " << partial[4] << "\n";
```

The output is:

```
7 8 0 0
```

The array has five elements, but the braces give values for only the first two. The rest are set to zero. This is a rule for every array that's given any initial values: any element without a value is zero for numbers, and empty for strings. Don't rely on it for variables, though. An ordinary `int` that you don't initialize holds whatever was in memory, and that's a different rule.

### Leaving out the size

If you give the values in the braces, the compiler can count them for you:

```cpp
std::string cars[] = {"Volvo", "BMW", "Ford", "Mazda", "Tesla"};
```

The square brackets are empty, and the array has five elements because five values are listed. Leaving out the size is safe when you initialize the array right away. It's a good habit when the list is fixed and you don't want to count it yourself.

### Finding the length

The next lines of the program ask for the number of elements:

```cpp
std::cout << "Cars: " << std::size(cars) << "\n";
std::cout << "Last: " << cars[std::size(cars) - 1] << "\n";
```

The output is:

```
Cars: 5
Last: Tesla
```

`std::size` comes from `<iterator>`, and it returns the number of elements in an array. Use it rather than counting by hand, because the count stays correct if you add an element later.

The last element is at index `std::size(cars) - 1`, which is 4 here, the position after the four steps from index 0. Writing the index this way means that the code still finds the last element if the list changes.

### Filling an array later

You can also declare an array with a size and leave the values until afterwards:

```cpp
int squares[3];
squares[0] = 1;
squares[1] = 4;
squares[2] = 9;
std::cout << squares[2] << "\n";
```

The output is `9`. Here the array exists before it has any values, so you have to set every element yourself. Until you do, the values are undefined, and reading one can give anything. The program sets all three elements before it reads any of them, which is the safe pattern.

Setting each element by hand works for a few values, but it doesn't scale. The loops chapter covers a loop that fills an array in one go.

---

### Quiz

*These questions are written for this course.*

````quiz
What does `int nums[5] = {1, 2};` store in `nums[4]`?
○ 4
→ Not quite. The index is 4, but the value stored there is not the index.
◉ 0
→ Yes. Elements without a listed value are set to zero.
○ An undefined value.
→ Not quite. When an array is given initial values, the unlisted elements are zero.
````

````quiz
What does `std::size(cars)` return for `std::string cars[] = {"a", "b", "c"};`?
○ 2
→ Not quite. That's the index of the last element, not the number of elements.
◉ 3
→ Yes. The array has three elements, so its size is 3.
○ The size in bytes.
→ Not quite. std::size counts elements. The size in bytes is what sizeof gives you.
````

---

### Try it in the runner

Change `partial` to `int partial[5] = {7, 8, 9, 10, 11};`, and predict the first line of output. Every element has a value now, so the line should read `7 8 9 11`, since `partial[2]` is 9 and `partial[4]` is 11.

Then delete the line that sets `squares[2]`, so `squares[2]` is never assigned, and press **Run**. The value printed is undefined. It may be zero, or it may be anything else, which is why every element should be set before it's read.

---

Arrays can be created in several ways, and `std::size` tells you how many elements they hold. The loops chapter is what makes arrays useful, because it lets you visit every element without writing out each index.
