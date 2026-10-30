// Calculator, with all three bonus items:
//   Bonus 1: exponents with ^ (right-associative, binds tighter than * and /)
//   Bonus 2: square roots with sqrt(...), and clear errors for negative arguments and unknown names
//   Bonus 3: square and curly brackets, which must match the bracket they close
// Rounding: results print with 15 significant digits, so 8^(1/3), which is 2.0000000000000004 in floating point,
// prints as 2. This is a choice about display, not a change to the value that is computed.

#include <cctype>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// The kinds of token the calculator reads. Brackets of every kind share Open and Close; the token's text says which.
enum class Kind { Number, Name, Plus, Minus, Star, Slash, Caret, Open, Close, End };

// One token: its kind, its text, its value if it's a number, and the column where it starts (counting from 1).
struct Token {
    Kind kind;
    std::string text;
    double value;
    std::size_t column;
};

// Throws an error whose message ends with the column, such as "division by zero at column 3".
[[noreturn]] void fail(const std::string& message, std::size_t column) {
    throw std::runtime_error(message + " at column " + std::to_string(column));
}

// How an error describes the token it found: its text, or "end of input".
std::string describe(const Token& token) {
    return token.kind == Kind::End ? "end of input" : "'" + token.text + "'";
}

// Splits the text into tokens. Each token records its column. The last token is always End, one column past the input.
std::vector<Token> tokenize(const std::string& text) {
    std::vector<Token> tokens;
    std::size_t i = 0;
    while (i < text.size()) {
        const char c = text[i];
        const std::size_t column = i + 1;
        if (std::isspace(static_cast<unsigned char>(c))) {
            i++;
            continue;
        }
        if (std::isdigit(static_cast<unsigned char>(c)) || c == '.') {
            std::string number;
            while (i < text.size() && (std::isdigit(static_cast<unsigned char>(text[i])) || text[i] == '.')) {
                number += text[i];
                i++;
            }
            int dots = 0;
            for (char d : number) {
                if (d == '.') dots++;
            }
            if (dots > 1 || number == ".") {
                throw std::runtime_error("invalid number '" + number + "' at column " + std::to_string(column));
            }
            tokens.push_back(Token{Kind::Number, number, std::stod(number), column});
            continue;
        }
        if (std::isalpha(static_cast<unsigned char>(c))) {
            std::string name;
            while (i < text.size() && std::isalnum(static_cast<unsigned char>(text[i]))) {
                name += text[i];
                i++;
            }
            tokens.push_back(Token{Kind::Name, name, 0.0, column});
            continue;
        }

        Kind kind = Kind::End;
        if (c == '+') {
            kind = Kind::Plus;
        } else if (c == '-') {
            kind = Kind::Minus;
        } else if (c == '*') {
            kind = Kind::Star;
        } else if (c == '/') {
            kind = Kind::Slash;
        } else if (c == '^') {
            kind = Kind::Caret;
        } else if (c == '(' || c == '[' || c == '{') {
            kind = Kind::Open;
        } else if (c == ')' || c == ']' || c == '}') {
            kind = Kind::Close;
        } else {
            fail("unexpected character '" + std::string(1, c) + "'", column);
        }
        tokens.push_back(Token{kind, std::string(1, c), 0.0, column});
        i++;
    }
    tokens.push_back(Token{Kind::End, "", 0.0, text.size() + 1});
    return tokens;
}

// Recursive descent. The grammar, with one function per rule:
//   expr    := term (('+' | '-') term)*
//   term    := factor (('*' | '/') factor)*
//   factor  := '-' factor | power
//   power   := primary ('^' factor)?
//   primary := number | open expr close | name open expr close
class Parser {
public:
    explicit Parser(std::vector<Token> tokens) : tokens_(std::move(tokens)) {}

    // Parses the whole input, and reports anything left over.
    double parseAll() {
        const double value = parseExpr();
        if (peek().kind != Kind::End) {
            fail("expected end of input, found " + describe(peek()), peek().column);
        }
        return value;
    }

private:
    std::vector<Token> tokens_;
    std::size_t pos_ = 0;

    const Token& peek() const {
        return tokens_[pos_];
    }

    // Moves past the current token and returns it. The End token is never moved past.
    Token advance() {
        Token token = tokens_[pos_];
        if (token.kind != Kind::End) {
            pos_++;
        }
        return token;
    }

    // expr := term (('+' | '-') term)*
    double parseExpr() {
        double value = parseTerm();
        while (peek().kind == Kind::Plus || peek().kind == Kind::Minus) {
            const Token op = advance();
            const double right = parseTerm();
            value = op.kind == Kind::Plus ? value + right : value - right;
        }
        return value;
    }

    // term := factor (('*' | '/') factor)*
    double parseTerm() {
        double value = parseFactor();
        while (peek().kind == Kind::Star || peek().kind == Kind::Slash) {
            const Token op = advance();
            const double right = parseFactor();
            if (op.kind == Kind::Star) {
                value *= right;
            } else {
                if (right == 0.0) {
                    fail("division by zero", op.column);
                }
                value /= right;
            }
        }
        return value;
    }

    // factor := '-' factor | power. The minus sign is applied after any power on its right, so -2^2 is -(2^2).
    double parseFactor() {
        if (peek().kind == Kind::Minus) {
            advance();
            return -parseFactor();
        }
        return parsePower();
    }

    // power := primary ('^' factor)?. The right side is a factor, so 2^3^2 is 2^(3^2), and 2^-1 is valid.
    double parsePower() {
        const double base = parsePrimary();
        if (peek().kind == Kind::Caret) {
            advance();
            const double exponent = parseFactor();
            return std::pow(base, exponent);
        }
        return base;
    }

    // primary := number | open expr close | name open expr close
    double parsePrimary() {
        const Token token = peek();
        if (token.kind == Kind::Number) {
            advance();
            return token.value;
        }
        if (token.kind == Kind::Open) {
            advance();
            const double value = parseExpr();
            expectClose(token.text);
            return value;
        }
        if (token.kind == Kind::Name) {
            advance();
            return parseFunction(token);
        }
        fail("expected a number or '(', found " + describe(token), token.column);
    }

    // Checks that the closing bracket matches the opening one. An opening '(' needs ')', and so on.
    void expectClose(const std::string& opener) {
        const std::string closer = opener == "(" ? ")" : opener == "[" ? "]" : "}";
        const Token& close = peek();
        if (close.kind != Kind::Close || close.text != closer) {
            fail("expected '" + closer + "', found " + describe(close), close.column);
        }
        advance();
    }

    // A function name must be followed by a bracketed argument. Only sqrt is known.
    double parseFunction(const Token& name) {
        if (name.text != "sqrt") {
            fail("unknown function '" + name.text + "'", name.column);
        }
        const Token open = peek();
        if (open.kind != Kind::Open) {
            fail("expected '(' after 'sqrt', found " + describe(open), open.column);
        }
        advance();
        const double argument = parseExpr();
        expectClose(open.text);
        if (argument < 0.0) {
            fail("sqrt of a negative number", name.column);
        }
        return std::sqrt(argument);
    }
};

// Formats a result with up to 15 significant digits. That hides small floating-point errors, so 2.0000000000000004
// prints as 2, and whole numbers print without a decimal point.
std::string formatResult(double value) {
    std::ostringstream out;
    out << std::setprecision(15) << value;
    return out.str();
}

// Evaluates one line of input, and returns the result as text. Errors are thrown.
std::string calculate(const std::string& text) {
    Parser parser(tokenize(text));
    return formatResult(parser.parseAll());
}

// Joins the words of the argument box back into one line, since the box splits what you type at each space.
std::string joinArguments(int argc, char* argv[]) {
    std::string text;
    for (int i = 1; i < argc; i++) {
        if (i > 1) {
            text += ' ';
        }
        text += argv[i];
    }
    return text;
}

// Each check is an input and its expected output. An error is expected as "error: " followed by its message.
// Returns the number of checks that failed.
int runChecks() {
    int failures = 0;
    auto check = [&failures](const std::string& text, const std::string& expected) {
        std::string actual;
        try {
            actual = calculate(text);
        } catch (const std::exception& error) {
            actual = std::string("error: ") + error.what();
        }
        const bool passed = actual == expected;
        std::cout << (passed ? "PASS " : "FAIL ") << text << " -> " << actual << "\n";
        if (!passed) {
            failures++;
        }
    };

    // The core examples and errors.
    check("2 + 3 * 4", "14");
    check("(2 + 3) * 4", "20");
    check("10 - 4 - 3", "3");
    check("8 / 4 / 2", "1");
    check("-3 + 5", "2");
    check("2 * -3", "-6");
    check("10 / 4", "2.5");
    check("1.5 * 4", "6");
    check("2 + $", "error: unexpected character '$' at column 5");
    check("1 / 0", "error: division by zero at column 3");
    check("(2 + 3", "error: expected ')', found end of input at column 7");
    check("2 + 3)", "error: expected end of input, found ')' at column 6");
    check("2 +", "error: expected a number or '(', found end of input at column 4");
    check("1.2.3", "error: invalid number '1.2.3' at column 1");

    // Bonus 1: exponents.
    check("2^3", "8");
    check("2 * 3^2", "18");
    check("2^3^2", "512");
    check("-2^2", "-4");
    check("2^-1", "0.5");

    // Bonus 2: square roots.
    check("sqrt(16)", "4");
    check("sqrt(2) * sqrt(2)", "2");
    check("8^(1/3)", "2");
    check("sqrt(-4)", "error: sqrt of a negative number at column 1");
    check("foo(2)", "error: unknown function 'foo' at column 1");

    // Bonus 3: brackets.
    check("{2 * [3 + 4]}", "14");
    check("(2 + 3]", "error: expected ')', found ']' at column 7");

    std::cout << "Failures: " << failures << "\n";
    return failures;
}

// Shows a fixed list of expressions, with each result or error, and returns.
void runDemo() {
    const std::vector<std::string> expressions = {
        "2 + 3 * 4", "(2 + 3) * 4", "10 - 4 - 3", "8 / 4 / 2", "-3 + 5", "2 * -3", "10 / 4", "1.5 * 4",
        "2^3", "2 * 3^2", "2^3^2", "-2^2", "2^-1", "sqrt(16)", "8^(1/3)", "{2 * [3 + 4]}",
        "2 + $", "1 / 0", "(2 + 3", "2 + 3)", "2 +", "1.2.3", "sqrt(-4)", "foo(2)", "(2 + 3]",
    };
    for (const std::string& expression : expressions) {
        try {
            std::cout << expression << " => " << calculate(expression) << "\n";
        } catch (const std::exception& error) {
            std::cout << expression << " => error: " << error.what() << "\n";
        }
    }
}

int main(int argc, char* argv[]) {
    const std::string request = joinArguments(argc, argv);
    if (request == "selftest") {
        return runChecks() == 0 ? 0 : 1;
    }
    if (request == "demo") {
        runDemo();
        return 0;
    }
    if (!request.empty()) {
        try {
            std::cout << calculate(request) << "\n";
            return 0;
        } catch (const std::exception& error) {
            std::cout << "error: " << error.what() << "\n";
            return 1;
        }
    }

    // The REPL: read a line, evaluate it, and print the result. Blank lines are skipped, and quit ends the loop.
    std::cout << "Calculator. Type an expression, or quit to exit.\n";
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "quit") {
            break;
        }
        if (line.find_first_not_of(" \t\r") == std::string::npos) {
            continue;
        }
        try {
            std::cout << calculate(line) << "\n";
        } catch (const std::exception& error) {
            std::cout << "error: " << error.what() << "\n";
        }
    }
    return 0;
}
