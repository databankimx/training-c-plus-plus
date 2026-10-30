## Walkthrough: Core calculator

The example is in `src/main.cpp`. It has three parts, which mirror the three stages of a calculator: tokenizing, parsing, and evaluating.

**Tokens.** `tokenize` walks the text one character at a time. It skips spaces, reads a run of digits and dots as one number, and turns each operator or bracket into its own token. Every token records its column, counting from 1, so an error can name the place where it happened. The last token is always `End`, one column past the input, which is where a message about "end of input" points.

A number with more than one dot, such as `1.2.3`, is rejected while it's being read, because the whole run of characters is the thing that's wrong. The check for a lone dot catches `.` on its own.

**The parser.** `Parser` holds the token list and a position. It has one function per grammar rule: `parseExpr`, `parseTerm`, and `parseFactor`. Each one reads what its rule describes, and calls the rule below it for each part. Precedence follows from that. `parseTerm` reads factors joined by `*` and `/`, and `parseExpr` reads terms joined by `+` and `-`. A term is finished before an expression adds to it, so multiplication happens first.

The loops in `parseExpr` and `parseTerm` make the operators left-associative. Each pass takes the value so far and the next term, so `10 - 4 - 3` is `(10 - 4) - 3`.

**Evaluation.** The parser computes each value as it reads, so there's no separate tree in this version. Division checks for zero, and reports the column of the `/` operator, which is the place a reader would look. The error messages come from `fail`, which adds the column to the message, so every error has the same shape.

**Output.** `formatResult` prints with 15 significant digits. That's the choice that makes `10 / 4` print as `2.5`, and `2 * 7` print as `14`, with no trailing zeros. It also hides small floating-point errors, which matters for the bonus items.

**Modes.** The arguments are joined back into one line, since the runner's argument box splits what you type at each space. `selftest` runs the checks, and `demo` prints the examples. With no arguments, the REPL reads lines until `quit`. The `selftest` mode is what CTest runs, through `add_test` in `CMakeLists.txt`.
