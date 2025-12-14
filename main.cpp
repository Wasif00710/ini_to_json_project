#include <bits/stdc++.h>
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "semantic/semantic.h"
#include "codegen/codegen.h"

using namespace std;

int main() {

    // 1. Lexical Analysis
    vector<Token> tokens = tokenize("config.ini");

    // 2. Syntax Analysis
    auto config = parse(tokens);

    // 3. Semantic Analysis
    auto typedConfig = analyze(config);

    // 4. Code Generation
    string json = generateJSON(typedConfig);

    // Output JSON
    cout << json;

    return 0;
}
