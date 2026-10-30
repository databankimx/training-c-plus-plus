#include <iostream>
#include <string>
#include <utility>

// A buffer that announces every construction, copy, move, and destruction, so the output shows which one ran.
class Buffer {
public:
    Buffer(std::string text) {
        data = text;
        std::cout << "Construct " << data << "\n";
    }

    // The copy constructor makes a new buffer with its own copy of the text.
    Buffer(const Buffer& other) {
        data = other.data;
        std::cout << "Copy " << data << "\n";
    }

    // The move constructor takes the text out of the other buffer, so no text is copied. The && marks an
    // rvalue reference, which can refer to an object that is about to be discarded.
    Buffer(Buffer&& other) {
        data = std::move(other.data);
        std::cout << "Move " << data << "\n";
    }

    ~Buffer() {
        std::cout << "Destroy " << data << "\n";
    }

private:
    std::string data;
};

int main() {
    Buffer a("alpha");
    Buffer b = a;               // copy: b gets its own copy of the text, and a keeps its text
    Buffer c = std::move(a);    // move: c takes the text from a, which is left empty

    std::cout << "All three objects are still valid to use.\n";

    // Try: add Buffer d = std::move(c); and predict the output, including what d's destructor prints.
    return 0;
}
