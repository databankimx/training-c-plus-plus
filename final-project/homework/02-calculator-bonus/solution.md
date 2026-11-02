## Walkthrough: Bonus items

The example is in `src/main.cpp`. It builds on the core, and adds three things. Each one is a small change to a part the core already has.

**Exponents.** `^` is a token, and `parsePower` handles it. The rule is `power := primary ('^' factor)?`, which sits between `factor` and `primary`. The right side of `^` is a `factor`, not a `primary`, and that's what makes the operator right-associative: `2^3^2` parses as `2^(3^2)`, which is 512. Because the minus sign is handled in `parseFactor`, above `parsePower`, `-2^2` gives `-(2^2)`. And because the right side is a factor, `2^-1` is valid.

**Square roots.** Letters and digits become a `Name` token in the tokenizer. In `parsePrimary`, a name is consumed, then `parseFunction` checks it. Only `sqrt` is known, so any other name is reported as unknown, at the name's own column. `sqrt` then needs an opening bracket, reads its argument, and checks that the argument is not negative before taking the root. The check is in the function, not the tokenizer, because only the value tells you the sign.

**Brackets.** The tokenizer sorts brackets into `Open` and `Close`, and the token's text says which bracket it is. `parsePrimary` accepts any opening bracket, and `expectClose` checks that the closing token matches it. The match is written once, in `expectClose`, so every kind of bracket is checked the same way.

**Rounding.** `pow` and `sqrt` can return a value that's off in the last binary digit. `8^(1/3)` may come out as 2.0000000000000004. The program prints with 15 significant digits, which shows it as 2. That's a choice about display, and it's explained in the comment above `formatResult`. The computed value is unchanged, so a comparison that needs exact equality should use a tolerance instead.
