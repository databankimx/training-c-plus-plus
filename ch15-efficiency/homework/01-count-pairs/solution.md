## Solution: Count pairs

The inner loop starts at `i + 1`, so each pair is visited once, with the smaller index first. The first outer pass pairs item 0 with every later item, the second pairs item 1 with the later ones, and so on. The counts are n − 1, then n − 2, down to 0, and they add up to n(n − 1)/2.

The formula evaluates the same sum directly. It does one multiplication and one division, whatever n is. The loops do about n²/2 operations, so for n = 100 they perform around 5,000 steps, and for n = 1000 about 500,000. Both give the same answer, but the formula's cost doesn't grow with n in the same way.

The loops are still worth having. They show where the number comes from, and they're the honest check on a formula you derived. A formula that disagrees with the loops has a mistake in it, and the loops are the quickest way to find out.

For the division, `n * (n - 1)` is always even, since one of the two factors is even, so the integer division is exact.
