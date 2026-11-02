#include <iostream>

class Employee {
protected:
    int monthlySalary = 0;

public:
    Employee(int salary) {
        monthlySalary = salary;
    }

    virtual int pay() const {
        return monthlySalary;
    }
};

class Manager : public Employee {
public:
    Manager(int salary, int extra) : Employee(salary) {
        bonus = extra;
    }

    int pay() const override {
        return monthlySalary + bonus;
    }

private:
    int bonus = 0;
};

void printPay(const Employee& worker) {
    std::cout << "Monthly pay: " << worker.pay() << "\n";
}

int main() {
    Employee clerk(3000);
    Manager boss(4500, 800);

    printPay(clerk);
    printPay(boss);

    return 0;
}
