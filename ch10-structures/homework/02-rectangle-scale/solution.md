## Solution: Rectangle scale

The structure's members have default values, so a rectangle created with no values is a unit square. The brace initialization `Rectangle r{3.0, 2.0};` sets width and height in declaration order.

`area` takes the rectangle by value. It reads the two members and returns their product, and it can't change the caller's rectangle, even by accident. `scale` takes a reference, so `r.width *= factor` and `r.height *= factor` change the rectangle that `main` owns.

Scaling both sides by 2 multiplies the area by 4, since the area is width times height. The second line of output is 24.00, which is four times 6.00. That's a useful check when you're unsure whether scale worked: the ratio of the two areas should be the square of the factor.

The formatting is set once, before the first output, and applies to both areas.
