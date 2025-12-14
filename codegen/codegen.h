#ifndef CODEGEN_H
#define CODEGEN_H

#include <bits/stdc++.h>
#include "../semantic/semantic.h"

using namespace std;

// generate JSON string from typed config
string generateJSON(map<string, map<string, TypedValue>> typedConfig);

#endif
