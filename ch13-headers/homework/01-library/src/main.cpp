#include "Book.h"
#include "Library.h"

int main() {
    Book dune("Dune");
    Book emma("Emma");
    emma.checkOut();

    Library lib;
    lib.add(dune);
    lib.add(emma);
    lib.printAll();

    return 0;
}
