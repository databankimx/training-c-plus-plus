## Summary: Inheritance and polymorphism

This chapter covered how one class can build on another, and how a single call can do different work for different objects.

* **A derived class inherits from a base.** `class Car : public Vehicle` gives `Car` the public members of `Vehicle`, and `Car` can add its own.
* **Inheritance chains.** A class can inherit from a class that inherits from another, and each one adds to the one above.
* **Access levels matter in derived classes.** `protected` members are visible to derived classes but not to outside code. `private` members are visible only inside their own class.
* **A class can have several bases.** `class Engineer : public Programmer, public Badge` gets the members of both.
* **`virtual` enables polymorphism.** A call through a base reference uses the version in the object's real class, decided at run time.
* **`override` checks the replacement.** A function that doesn't match a virtual function in its base is a compile error.
* **Pass polymorphic objects by reference.** A copy of a derived object passed as its base loses the derived part.

### Check your understanding

*These questions are written for this course.*

````quiz
Which member of a base class can a derived class use, but code outside the class hierarchy cannot?
○ public
→ Not quite. Public members are visible to everyone.
◉ protected
→ Yes. Protected members are visible to derived classes only.
○ private
→ Not quite. Private members are visible only inside their own class, not even to derived classes.
````

````quiz
Why is `virtual` needed for polymorphism?
○ It makes the derived class's function private.
→ Not quite. virtual has nothing to do with access.
◉ It makes a call through a base reference use the object's real class, at run time.
→ Yes. Without virtual, the compiler uses the reference's declared type instead.
○ It lets the function be called without an object.
→ Not quite. A virtual function is still called on an object.
````

````quiz
Why should a polymorphic parameter be a reference or pointer, rather than a copy?
○ Because copies cannot be made of classes.
→ Not quite. Classes can be copied. The problem is what the copy keeps.
◉ Because a copy of a derived object passed as its base loses the derived part, which is called slicing.
→ Yes. The derived class's version of the function is lost when only the base part is copied.
○ Because references are faster to call.
→ Not quite. The reason is correctness, not speed.
````
