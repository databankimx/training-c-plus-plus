## Protected members and multiple inheritance

Inheritance has three access levels that matter for members. `public` members are visible to everyone, and `private` members are visible only inside their own class. `protected` sits between them: a protected member is visible inside the class and in classes derived from it, but not to code outside that family.

Here's the program for this step, in `src/main.cpp`. The base class has a protected member:

```cpp
class Employee {
protected:
    int salary = 0;
};
```

The derived class can use `salary` directly, since it's inside the family:

```cpp
class Programmer : public Employee {
public:
    void setSalary(int s) {
        salary = s;
    }
    int getSalary() const {
        return salary;
    }
};
```

`main` can't touch `salary`, since it's outside the family. The functions the class provides are the only way to read and change it, which is encapsulation again.

Press **Run**. The output is:

```
Salary: 50000
Bonus: 15000
Badge: B-42
```

### More than one base

A class can inherit from several bases at once, separated by commas:

```cpp
class Engineer : public Programmer, public Badge {};
```

`Engineer` gets the members of `Programmer`, which include `salary`, `bonus`, and the functions, and the members of `Badge`, which include `code`. Each base contributes its own members, and `e.code` works alongside `e.bonus`.

Multiple inheritance is powerful, and it's also the source of most of the complexity in inheritance. When two bases have members with the same name, a derived class has to say which one it means. Keep the bases independent, and avoid two bases that share a common ancestor, since that case needs extra rules this course doesn't cover.

### Choosing the access level

The rule for choosing is simple. Make a member `private` if only the class needs it. Make it `protected` if derived classes need it to do their job. Make it `public` only when the rest of the program needs it. Each step outward gives more code the power to change the member, so the smallest level that works is the safest.

---

### Quiz

*These questions are written for this course.*

````quiz
Which code can read a protected member of a base class?
○ main, which is outside the class.
→ Not quite. Code outside the class hierarchy can't read protected members.
◉ A class derived from the base.
→ Yes. Protected members are visible inside derived classes.
○ Any object of the base class, from anywhere.
→ Not quite. Protected is not public, so outside code can't use it through an object.
````

````quiz
What does `class Engineer : public Programmer, public Badge {};` do?
○ It creates two Engineer objects.
→ Not quite. The declaration creates a type, not objects.
◉ It makes Engineer inherit the members of both Programmer and Badge.
→ Yes. A class can have more than one base.
○ It copies the members of Badge into Programmer.
→ Not quite. Each base keeps its own members, and the derived class gets both sets.
````

---

### Try it in the runner

Add `e.salary = 60000;` to `main`, and predict whether it compiles before you press **Run**. It doesn't. `salary` is protected, so `main` can't use it, even through an `Engineer`.

Then change `salary` to `public` in `Employee`, and press **Run** again. The build now succeeds, which is the reason protected exists: public access lets every part of the program change the salary, which is exactly what encapsulation prevents. Change it back to `protected`.

---

Protected members give derived classes access without opening a member to everyone, and multiple inheritance lets a class combine several bases. The next step covers polymorphism, which lets one call behave differently depending on the object it's made on.
