#ifndef SEMANTIC_H
#define SEMANTIC_H

#include <bits/stdc++.h>
#include "../parser/parser.h"   // ⭐ REQUIRED
using namespace std;

struct TypedValue {
    string type;
    string value;
    int line;
};

struct SchemaRule {
    string type;
    bool required;
};

map<string, map<string, SchemaRule>>
loadSchema(const string& filename);

map<string, map<string, TypedValue>>
analyze(map<string, map<string, ParsedValue>> config,
        map<string, map<string, SchemaRule>> schema);

#endif
