## Summary: Classes

This chapter covered classes, which group data with the functions that work on it.

* **A class is a type, and its variables are objects.** `class` makes the default member access private, where `struct` makes it public.
* **Access labels control visibility.** `public` members are the interface, and `private` members are hidden from outside code.
* **A method is a function that belongs to a class.** It's called on an object, and it uses that object's members directly. A method that only reads should be `const`.
* **A constructor sets up an object when it's created.** It has the class's name and no return type, and it takes whatever arguments an object needs.
* **Brace initialization calls the constructor.** Once a class has a constructor, its arguments must match the constructor's parameters.
* **Encapsulation keeps the rules in one place.** Private data, with setters that check each change, means an object can't be left in a state its class doesn't allow.

### Check your understanding

*These questions are written for this course.*

````quiz
What is a class's default member access?
○ public
→ Not quite. That's the default for a struct.
◉ private
→ Yes. A class hides its members unless a label makes them public.
○ protected
→ Not quite. Protected is not the default for either keyword.
````

````quiz
Why should a method that only reads its object be declared const?
○ Because const methods run faster.
→ Not quite. The keyword is about what the method may change, not speed.
◉ So the compiler checks that it doesn't change the object, and it can be called on a const object.
→ Yes. const is a promise the compiler enforces.
○ Because const is required for every method.
→ Not quite. It's optional, but it's the right choice for methods that only read.
````

````quiz
A class has a constructor that takes a brand, a model, and a year. Which creation is valid?
○ Car myCar;
→ Not quite. With a constructor taking arguments, there is no default constructor to use.
◉ Car myCar("Ford", "Mustang", 1969);
→ Yes. The arguments match the constructor's parameters.
○ Car myCar("Ford");
→ Not quite. The constructor needs all three arguments.
````
