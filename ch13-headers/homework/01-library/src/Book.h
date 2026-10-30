#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
public:
    Book(std::string bookTitle = "untitled");
    void print() const;
    void checkOut();

private:
    std::string title;
    bool available = true;
};

#endif
