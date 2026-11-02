#include <cctype>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// Core calculator. Bonus items are not included in this version.

// The kinds of token the calculator reads.
enum class Kind { Number, Plus, Minus, Star, Slash, LeftParen, RightParen, End };

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

        Kind kind = Kind::End;
        if (c == '+') {
            kind = Kind::Plus;
        } else if (c == '-') {
            kind = Kind::Minus;
        } else if (c == '*') {
            kind = Kind::Star;
        } else if (c == '/') {
            kind = Kind::Slash;
        } else if (c == '(') {
            kind = Kind::LeftParen;
        } else if (c == ')') {
            kind = Kind::RightParen;
        } else {
            fail("unexpected character '" + std::string(1, c) + "'", column);
        }
        tokens.push_back(Token{kind, std::string(1, c), 0.0, column});
        i++;
    }
    tokens.push_back(Token{Kind::End, "", 0.0, text.size() + 1});
    return tokens;
}

// Recursive descent: one function per grammar rule. Each rule calls the rules below it, so precedence follows from the
// structure of the functions.
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

    // factor := '-' factor | number | '(' expr ')'
    double parseFactor() {
        if (peek().kind == Kind::Minus) {
            advance();
            return -parseFactor();
        }
        const Token token = peek();
        if (token.kind == Kind::Number) {
            advance();
            return token.value;
        }
        if (token.kind == Kind::LeftParen) {
            advance();
            const double value = parseExpr();
            if (peek().kind != Kind::RightParen) {
                fail("expected ')', found " + describe(peek()), peek().column);
            }
            advance();
            return value;
        }
        fail("expected a number or '(', found " + describe(token), token.column);
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

    std::cout << "Failures: " << failures << "\n";
    return failures;
}

// Shows a fixed list of expressions, with each result or error, and returns.
void runDemo() {
    const std::vector<std::string> expressions = {
        "2 + 3 * 4", "(2 + 3) * 4", "10 - 4 - 3", "8 / 4 / 2", "-3 + 5", "2 * -3", "10 / 4", "1.5 * 4",
        "2 + $", "1 / 0", "(2 + 3", "2 + 3)", "2 +", "1.2.3",
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
