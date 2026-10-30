#include <iostream>

class Animal {
public:
    // virtual lets a derived class replace this function, and calls through a base reference use the replacement.
    virtual void sound() const {
        std::cout << "The animal makes a sound...\n";
    }
};

class Pig : public Animal {
public:
    void sound() const override {
        std::cout << "The pig says: oink oink!\n";
    }
};

class Dog : public Animal {
public:
    void sound() const override {
        std::cout << "The dog says: bow wow!\n";
    }
};

// The parameter is a reference to an Animal. The object passed in may be any Animal or a class derived from one.
void makeSound(const Animal& animal) {
    animal.sound();
}

int main() {
    Animal generic;
    Pig pig;
    Dog dog;

    makeSound(generic);
    makeSound(pig);
    makeSound(dog);

    // Try: remove virtual from Animal::sound and override from the two derived classes. Predict the output of makeSound(pig).
    return 0;
}
