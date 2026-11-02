## Solution: Numbered copy

The example opens the input and the output, and checks both. The check on the output matters as much as the check on the input: a folder that can't be written to would otherwise discard every line silently.

The loop reads with `std::getline` and increments `count` before writing, so the first line is numbered 1. Incrementing after writing would number the lines from 0, or leave the counter one short when the loop ends.

Both files are closed explicitly before the final message. The View button opens the output file, and closing first guarantees that its text is complete on disk.

The count printed at the end comes from the same variable as the numbers, so the two can't disagree.
