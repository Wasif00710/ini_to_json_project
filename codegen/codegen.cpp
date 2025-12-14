#include "codegen.h"

string generateJSON(map<string, map<string, TypedValue>> typedConfig) {

    string json = "{\n";
    bool firstSection = true;

    for (auto sec : typedConfig) {

        if (!firstSection) json += ",\n";
        firstSection = false;

        json += "  \"" + sec.first + "\": {\n";

        bool firstKey = true;
        for (auto kv : sec.second) {

            if (!firstKey) json += ",\n";
            firstKey = false;

            json += "    \"" + kv.first + "\": ";

            if (kv.second.type == "string") {
                json += "\"" + kv.second.value + "\"";
            }
            else {
                json += kv.second.value; // int or bool
            }
        }

        json += "\n  }";
    }

    json += "\n}\n";
    return json;
}
