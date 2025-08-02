// include/token.h
#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    LET,
    IDENTIFIER,
    ASSIGN,
    NUMBER,
    PRINT,
    LPAREN,
    RPAREN,
    SEMICOLON,
    PLUS,
    END_OF_FILE,
    UNKNOWN
};

struct Token {
    TokenType type;
    std::string value;

    Token(TokenType t, const std::string& v) : type(t), value(v) {}
};

#endif // TOKEN_H
