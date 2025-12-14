#ifndef CODEGEN_H
#define CODEGEN_H

#include <bits/stdc++.h>
#include "../semantic/semantic.h"
using namespace std;

// JSON generator
string generateJSON(map<string, map<string, TypedValue>> typedConfig);

// YAML generator
string generateYAML(map<string, map<string, TypedValue>> typedConfig);

#endif
