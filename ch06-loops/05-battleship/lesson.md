## Battleship

This step puts the chapter together in one program: a two-dimensional array holds the state of the game, a `while` loop keeps the game going, and `if` and `else` decide what each move does. It's also the first program in the course that plays against the person using it.

Here's the grid, from the top of `src/main.cpp`:

```cpp
int ships[4][4] = {
    {0, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 0}
};
```

A `1` marks a square with a ship, and a `0` marks water. The grid has four ships in total: two in the first row, and two in the third column. The game ends when all four have been hit.

Press **Run**. The Output pane asks for a row, then a column. Each answer is typed into the input box, and Enter sends it. The program then reports a hit or a miss, and asks again.

### The game loop

The game is a `while` loop, which runs while there are ships left:

```cpp
while (hits < 4) {
    // ask for a row and column, then check the square
}
```

Each pass asks for a move, checks the grid, and updates the count of hits. `hits` starts at 0, and the loop ends once it reaches 4. The `turns` counter goes up on every valid move, so it can report the score at the end.

### Checking the square

Once the program has a row and a column, it looks up that square with two indexes:

```cpp
if (ships[row][column] == 1) {
    ships[row][column] = 0;
    hits++;
    std::cout << "Hit! " << (4 - hits) << " left.\n\n";
} else {
    std::cout << "Miss\n\n";
}
```

A hit sets the square to 0, so the same square can't count twice. Setting it to 0 is how the program remembers the hit. The message reports how many ships are left, which is `4 - hits`, since four ships start the game.

Notice that the grid is the only record of which squares have been hit. The program doesn't need a separate list of ships. The array's contents are the game state, and changing an element changes the game.

### Checking the input

The program checks the row and column before it uses them as indexes:

```cpp
if (row < 0 || row > 3 || column < 0 || column > 3) {
    std::cout << "Please choose numbers from 0 to 3.\n\n";
    continue;
}
```

The original tutorial version skips this check. With a row of 4, the program would read past the end of the grid, which is undefined. The `continue` skips the rest of the pass, so the bad move doesn't count as a turn, and the loop asks again. The same use of `continue` as in the break and continue step, and the same reason for it, applies here.

If you type a word where a number is expected, `cin` can't turn it into an `int`, so the read fails. A failed stream refuses every later read until you reset it, and the word stays in the input, so reading again would fail on the same word. That's why this program does three things after a failed read. It calls `std::cin.clear()` to reset the stream, it calls `std::cin.ignore(10000, '\n')` to throw away the rest of the line, and it uses `continue` to ask again. Without those steps, the prompts repeat forever. This is the same pattern you'll use for any input that might be bad.

### Quitting

The same failed read gives the player a way out. Before the program says the input is bad, it reads the character that caused the failure. If that character is `q`, the `break` leaves the loop, and the game ends with a message about the ships left. The check accepts `Q` too. The **Stop** button still works, but a player shouldn't need it to leave a game.

The quit check only looks at the first character, so `quit` also ends the game. Everything after the `q` is ignored, because the program leaves the loop and doesn't read again.

---

### Quiz

*These questions are written for this course.*

````quiz
Why does the game set a hit square to 0?
○ To hide the square from the player.
→ Not quite. The player is never shown the grid, so hiding it isn't the issue.
◉ So the same square can't count as a hit twice.
→ Yes. The grid records which squares still have ships.
○ Because 0 is the default value of an array.
→ Not quite. That's true, but it isn't why the program sets the value.
````

````quiz
A player enters row 4. What does the `continue` in the check do?
○ It ends the game.
→ Not quite. continue doesn't end the loop.
◉ It skips the rest of this pass, so the move isn't counted and the loop asks again.
→ Yes. The bad move doesn't reach the grid, and the loop goes around again.
○ It counts the move as a miss.
→ Not quite. A rejected move isn't checked against the grid at all.
````

---

### Try it in the runner

Type `x` at the row prompt, and check that the program says it needs a number and asks again, rather than repeating forever. Then type `q` at the column prompt, and check that the game ends with the quit message. Then play a game, and count the hits. Each square with a 1 is a hit, and the game ends after four. Then change a `1` in the grid to a `0`, and predict whether the game still ends after four hits. It doesn't: the loop needs four hits, and there are only three ships now, so the loop never finishes.

Then change `hits < 4` to `hits < 3`, and predict how the game ends. It stops after three hits, while the fourth ship is still on the grid, and the victory message is wrong. The loop's condition and the grid have to agree.

---

Battleship uses every idea in this chapter: the two-dimensional array holds the state, the loop keeps the game going, and the checks decide each move. The summary covers the chapter's loops together, and the homework practices them on their own.
