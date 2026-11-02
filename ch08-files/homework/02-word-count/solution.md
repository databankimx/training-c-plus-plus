## Solution: Word count

The example makes two passes over the file, each with its own stream. The first counts lines with `std::getline`, which reads a line and stops at its end. The second counts words with `>>`, which skips any run of whitespace, so spaces and line breaks both separate words.

The two streams are closed as soon as each pass finishes, so the second open starts with a clean file. Opening a file twice is cheap for a file this size, and it avoids the rewinding that a single stream would need.

The count of 11 is the answer to check against. The last line of the sample, `The end.`, contributes two words, and `dog.` contributes one, since punctuation stays attached to the word it follows.
