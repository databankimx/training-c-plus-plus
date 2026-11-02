## Pointers and arrays

You've used `numbers[1]` for an element of an array, and the functions chapter said that an array parameter receives a pointer to its first element. This step shows why those two ideas are the same thing.

Here's the program for this step, in `src/main.cpp`:

```cpp
int numbers[3] = {10, 20, 30};
int* first = numbers;
```

The name `numbers`, used on its own, gives the address of its first element. So `first` points at 10. No `&` is needed, since the array's name already works as an address.

Press **Run**. The output is:

```
10
20
30
```

The program prints three elements, each in a different way. `*first` reads the value at the address, which is 10. `first[1]` uses square brackets on a pointer, and gives the element one step past it, which is 20. `*(first + 2)` adds 2 to the pointer, and reads the element two steps along, which is 30.

### Adding to a pointer

Adding a number to a pointer moves it by that many elements, not by that many bytes. `first + 2` points two `int`s past `first`, whatever the size of an `int` on your system. That's why `first + 2` is the third element and not part of a byte count.

Square brackets are a shorthand for this: `first[1]` means `*(first + 1)`. The two forms always give the same element. You can write `numbers[1]` for the same reason, since the name of an array is a pointer to its first element.

### Why the function needed a count

This explains the functions step. Inside `printNumbers(int numbers[], int count)`, the parameter is really an `int*`, and `numbers[i]` is `*(numbers + i)`. The function can reach any element it's pointed at, but it has no way to find the end. That's why `count` is needed, and why `std::size` doesn't work on the parameter.

Keep the two meanings apart. In `main`, `numbers` is the whole array, and `std::size(numbers)` works. Inside the function, `numbers` is a pointer, and it isn't.

---

### Quiz

*These questions are written for this course.*

````quiz
With `int* first = numbers;`, what is `first[2]` for `int numbers[3] = {10, 20, 30};`?
○ 10
→ Not quite. That's first[0], the first element.
◉ 30
→ Yes. first[2] is *(first + 2), the third element.
○ 20
→ Not quite. That's first[1], the second element.
````

````quiz
Inside a function that receives `int* numbers`, why can't `std::size` find the number of elements?
○ Because std::size only works on strings.
→ Not quite. std::size works on arrays, and it has no meaning for a pointer.
◉ Because numbers is a pointer, and it holds no record of how many elements follow.
→ Yes. The pointer shows where the first element is, but not where the array ends.
○ Because pointers can't be read.
→ Not quite. A pointer can be read, through the dereference operator.
````

---

### Try it in the runner

Set `first = &numbers[2];`, and predict what `*first` shows before you press **Run**. It shows 30, since `&numbers[2]` is the address of the third element.

Then change `first` to point at `numbers[0]` again, and predict the output of `first[2]`. It's 30 again, since the square brackets reach two elements past the pointer.

---

An array's name is a pointer to its first element, and square brackets are a way to reach elements from it. That's the link that explains the functions chapter. The next chapter covers loops, which are how a program visits every element without writing each index by hand.
