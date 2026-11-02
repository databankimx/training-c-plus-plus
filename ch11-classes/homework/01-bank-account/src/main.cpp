#include <iomanip>
#include <iostream>
#include <stdexcept>

class BankAccount {
public:
    BankAccount(double opening) {
        if (opening < 0) {
            throw std::invalid_argument("opening balance cannot be negative");
        }
        balance = opening;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("Deposit must be positive.");
        }
        balance += amount;
    }

    void withdraw(double amount) {
        if (amount > balance) {
            throw std::runtime_error("Insufficient funds.");
        }
        balance -= amount;
    }

    double getBalance() const {
        return balance;
    }

private:
    double balance = 0.0;
};

int main() {
    std::cout << std::fixed << std::setprecision(2);

    BankAccount account(0.0);
    account.deposit(100.0);
    account.withdraw(30.0);
    std::cout << "Balance: " << account.getBalance() << "\n";

    try {
        account.withdraw(500.0);
    } catch (const std::exception& error) {
        std::cout << error.what() << "\n";
    }

    try {
        account.deposit(-5.0);
    } catch (const std::exception& error) {
        std::cout << error.what() << "\n";
    }

    std::cout << "Balance: " << account.getBalance() << "\n";
    return 0;
}
