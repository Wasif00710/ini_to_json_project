#ifndef LEXER_H
#define LEXER_H

#include <bits/stdc++.h>
using namespace std;

enum TokenType {
    SECTION,
    KEY,
    VALUE,
    ASSIGN,
    NEWLINE
};

struct Token {
    TokenType type;
    string text;
    int line;   // ⭐ NEW
};

vector<Token> tokenize(const string& filename);

#endif
