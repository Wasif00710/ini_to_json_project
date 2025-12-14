#include "semantic.h"

// check integer
bool isInt(string s) {
    if (s.size() == 0) return false;
    for (char c : s)
        if (!isdigit(c)) return false;
    return true;
}

// check boolean
bool isBool(string s) {
    for (char &c : s) c = tolower(c);
    return (s == "true" || s == "false");
}

map<string, map<string, TypedValue>>
analyze(map<string, map<string, string>> config) {

    map<string, map<string, TypedValue>> typedConfig;

    for (auto sec : config) {
        for (auto kv : sec.second) {

            string value = kv.second;
            TypedValue tv;

            if (isBool(value)) {
                tv.type = "bool";
                for (char &c : value) c = tolower(c);
                tv.value = value;
            }
            else if (isInt(value)) {
                tv.type = "int";
                tv.value = value;
            }
            else {
                tv.type = "string";
                tv.value = value;
            }

            typedConfig[sec.first][kv.first] = tv;
        }
    }

    return typedConfig;
}
