#include "Library.h"

void Library::add(const Book& book) {
    if (used < 3) {
        books[used] = book;
        used++;
    }
}

void Library::printAll() const {
    for (int i = 0; i < used; i++) {
        books[i].print();
    }
}
