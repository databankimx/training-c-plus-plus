#include "Book.h"

#include <iostream>

Book::Book(std::string bookTitle) {
    title = bookTitle;
}

void Book::print() const {
    std::cout << title << " - " << (available ? "available" : "checked out") << "\n";
}

void Book::checkOut() {
    available = false;
}
