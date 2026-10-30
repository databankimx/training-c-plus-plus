#include <iostream>
#include <string>

// Each member has a default value. A variable that doesn't set a member gets the default.
struct Settings {
    std::string name = "default";
    int volume = 5;
    bool muted = false;
};

void show(Settings s) {
    std::cout << s.name << " " << s.volume << " " << (s.muted ? "yes" : "no") << "\n";
}

int main() {
    Settings a;                      // every member takes its default
    Settings b{"Scott", 9, true};    // brace initialization, in the order the members are declared
    Settings c = b;                  // a copy of b
    c.volume = 1;                    // changes only c

    show(a);
    show(b);
    show(c);

    // Try: write Settings d{"Ada"}; and show(d). Predict the volume and muted values before you press Run.
    return 0;
}
