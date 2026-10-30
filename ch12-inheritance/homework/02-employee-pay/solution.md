## Solution: Employee pay

`printPay` takes an `Employee` by reference, and calls `pay()` on it. The function doesn't know whether it's given a clerk or a manager, and it doesn't need to. The `virtual` keyword on `Employee::pay` makes the call use the object's own version, so the second line prints the manager's total of 5300.

The `Manager` constructor passes the salary to the base class with `: Employee(salary)`. The base class has to be built before the derived class's own members are set, and this is the way to pass arguments up to it. The bonus is then stored in the manager's own member.

`Manager::pay` reads `monthlySalary`, which is protected in `Employee`, so the derived class can use it. It reads `bonus`, which is private to `Manager`, and that's fine too, since the code is inside the class.

For the first extension, `bonus` needs to be protected for `Director` to reach it. The second extension is the slicing case from the lesson: passing the `Employee` by value makes a copy that keeps only the `Employee` part, so the manager's total of 5300 is lost, and the output reverts to 4500.
