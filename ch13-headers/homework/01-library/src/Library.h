#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"

class Library {
public:
    void add(const Book& book);
    void printAll() const;

private:
    Book books[3];
    int used = 0;
};

#endif
