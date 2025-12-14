#ifndef SEMANTIC_H
#define SEMANTIC_H

#include <bits/stdc++.h>
using namespace std;

// value with type
struct TypedValue {
    string type;   // "int", "bool", "string"
    string value;
};

// semantic analysis function
map<string, map<string, TypedValue>>
analyze(map<string, map<string, string>> config);

#endif
