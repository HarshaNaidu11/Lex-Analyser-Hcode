#include "lexer.h"
#include <cctype>
#include <unordered_map>
#include <iostream>

static std::unordered_map<std::string, TokenType> keywords = {
    {"let", TokenType::LET},
    {"function", TokenType::FUNCTION},
    {"if", TokenType::IF},
    {"else", TokenType::ELSE},
    {"while", TokenType::WHILE},
    {"for", TokenType::FOR},
    {"return", TokenType::RETURN},
    {"switch", TokenType::SWITCH},
    {"case", TokenType::CASE},
    {"default", TokenType::DEFAULT},
    {"break", TokenType::BREAK},
    {"continue", TokenType::CONTINUE},
    {"true", TokenType::TRUE},
    {"false", TokenType::FALSE},
    {"class", TokenType::CLASS},
    {"struct", TokenType::STRUCT},
    {"print", TokenType::PRINT},
    {"input", TokenType::INPUT}
};

class Lexer {
    const std::string& src;
    size_t start = 0;
    size_t current = 0;
    int line = 1;
    std::vector<Token> tokens;

public:
    Lexer(const std::string& source) : src(source) {}

    std::vector<Token> scanTokens() {
        while (!isAtEnd()) {
            start = current;
            scanToken();
        }
        tokens.emplace_back(TokenType::END_OF_FILE, "", line);
        return tokens;
    }

private:
    bool isAtEnd() const {
        return current >= src.size();
    }

    char advance() {
        return src[current++];
    }

    bool match(char expected) {
        if (isAtEnd() || src[current] != expected) return false;
        current++;
        return true;
    }

    char peek() const {
        return isAtEnd() ? '\0' : src[current];
    }

    char peekNext() const {
        return (current + 1 >= src.size()) ? '\0' : src[current + 1];
    }

    void addToken(TokenType type) {
        std::string text = src.substr(start, current - start);
        tokens.emplace_back(type, text, line);
    }

    void scanToken() {
        char c = advance();
        switch (c) {
            case '+': addToken(TokenType::PLUS); break;
            case '-': addToken(TokenType::MINUS); break;
            case '*': addToken(TokenType::STAR); break;
            case '/':
                if (match('/')) {
                    while (peek() != '\n' && !isAtEnd()) advance();  // single-line comment
                } else {
                    addToken(TokenType::SLASH);
                }
                break;
            case '%': addToken(TokenType::MOD); break;
            case '=': addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL); break;
            case '!': addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::NOT); break;
            case '<': addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS); break;
            case '>': addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER); break;
            case '&': if (match('&')) addToken(TokenType::AND); break;
            case '|': if (match('|')) addToken(TokenType::OR); break;
            case ';': addToken(TokenType::SEMICOLON); break;
            case ',': addToken(TokenType::COMMA); break;
            case '.': addToken(TokenType::DOT); break;
            case '(': addToken(TokenType::LPAREN); break;
            case ')': addToken(TokenType::RPAREN); break;
            case '{': addToken(TokenType::LBRACE); break;
            case '}': addToken(TokenType::RBRACE); break;
            case '[': addToken(TokenType::LBRACKET); break;
            case ']': addToken(TokenType::RBRACKET); break;

            case ' ':
            case '\r':
            case '\t':
                break;
            case '\n':
                line++;
                break;

            case '"': string(); break;

            default:
                if (std::isdigit(c)) {
                    number();
                } else if (std::isalpha(c) || c == '_') {
                    identifier();
                } else {
                    tokens.emplace_back(TokenType::INVALID, std::string(1, c), line);
                }
                break;
        }
    }

    void string() {
        while (peek() != '"' && !isAtEnd()) {
            if (peek() == '\n') line++;
            advance();
        }

        if (isAtEnd()) {
            tokens.emplace_back(TokenType::INVALID, "Unterminated string", line);
            return;
        }

        advance(); // closing "
        std::string value = src.substr(start + 1, current - start - 2);
        tokens.emplace_back(TokenType::STRING, value, line);
    }

    void number() {
        while (std::isdigit(peek())) advance();
        addToken(TokenType::NUMBER);
    }

    void identifier() {
        while (std::isalnum(peek()) || peek() == '_') advance();
        std::string text = src.substr(start, current - start);
        TokenType type = keywords.count(text) ? keywords[text] : TokenType::IDENTIFIER;
        tokens.emplace_back(type, text, line);
    }
};

std::vector<Token> tokenize(const std::string& source) {
    Lexer lexer(source);
    return lexer.scanTokens();
}
