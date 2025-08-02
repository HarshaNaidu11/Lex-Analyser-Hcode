// src/lexer.h
#pragma once
#include <string>
#include <vector>

enum class TokenType {
    // Keywords
    LET, FUNCTION, IF, ELSE, WHILE, FOR, RETURN, SWITCH, CASE, DEFAULT, BREAK, CONTINUE,
    TRUE, FALSE, CLASS, STRUCT, PRINT, INPUT,

    // Operators
    PLUS, MINUS, STAR, SLASH, MOD,
    EQUAL, EQUAL_EQUAL, BANG_EQUAL,
    LESS, LESS_EQUAL, GREATER, GREATER_EQUAL,
    AND, OR, NOT,

    // Symbols
    SEMICOLON, COMMA, DOT,
    LPAREN, RPAREN, LBRACE, RBRACE,
    LBRACKET, RBRACKET,

    // Literals
    IDENTIFIER, NUMBER, STRING,

    // Special
    END_OF_FILE, INVALID
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;

    Token(TokenType t, std::string l, int ln) : type(t), lexeme(std::move(l)), line(ln) {}
};

std::vector<Token> tokenize(const std::string& source);
