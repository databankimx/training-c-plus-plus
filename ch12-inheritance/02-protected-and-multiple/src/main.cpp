#include <iostream>
#include <string>

// protected members are visible to derived classes, but not to code outside the class hierarchy.
class Employee {
protected:
    int salary = 0;
};

class Programmer : public Employee {
public:
    int bonus = 0;

    void setSalary(int s) {
        salary = s;
    }

    int getSalary() const {
        return salary;
    }
};

// A second base class. A class can inherit from more than one base at once.
class Badge {
public:
    std::string code = "B-42";
};

// Engineer inherits from both Programmer and Badge, so it has the members of each.
class Engineer : public Programmer, public Badge {};

int main() {
    Engineer e;
    e.setSalary(50000);
    e.bonus = 15000;

    std::cout << "Salary: " << e.getSalary() << "\n";
    std::cout << "Bonus: " << e.bonus << "\n";
    std::cout << "Badge: " << e.code << "\n";

    // Try: write e.salary = 60000; in main. Predict whether it compiles, and explain why.
    return 0;
}
