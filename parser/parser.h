#ifndef PARSER_H
#define PARSER_H

#include <bits/stdc++.h>
#include "../lexer/lexer.h"
using namespace std;

struct ParsedValue {
    string value;
    int line;
};

map<string, map<string, ParsedValue>>
parse(const vector<Token>& tokens);

#endif
