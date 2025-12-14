#include <bits/stdc++.h>
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "semantic/semantic.h"
#include "codegen/codegen.h"

using namespace std;

int main(int argc, char* argv[]) {

    if (argc < 4) {
        cout << "Usage:\n";
        cout << "  ini2json <config.ini> <schema.ini> <json|yaml>\n";
        return 1;
    }

    string configFile = argv[1];
    string schemaFile = argv[2];
    string format = argv[3];

    auto tokens = tokenize(configFile);
    auto parsedConfig = parse(tokens);
    auto schema = loadSchema(schemaFile);
    auto typedConfig = analyze(parsedConfig, schema);

    if (format == "json") {
        cout << generateJSON(typedConfig);
    }
    else if (format == "yaml") {
        cout << generateYAML(typedConfig);
    }
    else {
        cout << "Unknown format. Use 'json' or 'yaml'\n";
    }

    return 0;
}
