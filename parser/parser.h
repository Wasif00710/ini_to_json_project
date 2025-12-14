#ifndef PARSER_H
#define PARSER_H

#include <bits/stdc++.h>
#include "../lexer/lexer.h"

using namespace std;

// function that builds config structure from tokens
map<string, map<string, string>> parse(vector<Token> tokens);

#endif
