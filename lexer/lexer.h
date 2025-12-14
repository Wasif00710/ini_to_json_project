#ifndef LEXER_H
#define LEXER_H

#include <bits/stdc++.h>

enum TokenType {
    SECTION,
    KEY,
    VALUE,
    ASSIGN,
    NEWLINE
};

struct Token {
    TokenType type;
    std::string text;
};

std::vector<Token> tokenize(const std::string& filename);

#endif
