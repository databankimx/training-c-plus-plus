## Solution: Countdown

The loop starts at the number the user enters, and counts down with `--i`. The condition `i > 0` keeps the loop going while the counter is still positive, and stops it once the counter reaches 0. So the numbers printed run from the start down to 1, and the 0 is never printed.

The announcement sits after the loop. It runs once, whatever the starting number, so it isn't part of the loop body.

The `0` case in the requirements is where the condition matters most. With a starting value of 0, the test `i > 0` is false on the first check, and the loop never runs, so only `Liftoff!` prints. Changing the test to `i >= 0` would print an extra 0 at the end of every countdown, which the requirements don't want.
