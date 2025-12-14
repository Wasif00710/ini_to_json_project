#include "codegen.h"

// ---------------- JSON CODEGEN ----------------
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

            if (kv.second.type == "string")
                json += "\"" + kv.second.value + "\"";
            else
                json += kv.second.value;
        }

        json += "\n  }";
    }

    json += "\n}\n";
    return json;
}

// ---------------- YAML CODEGEN ----------------
string generateYAML(map<string, map<string, TypedValue>> typedConfig) {

    string yaml = "";

    for (auto sec : typedConfig) {

        yaml += sec.first + ":\n";

        for (auto kv : sec.second) {
            yaml += "  " + kv.first + ": ";

            if (kv.second.type == "string")
                yaml += "\"" + kv.second.value + "\"\n";
            else
                yaml += kv.second.value + "\n";
        }
        yaml += "\n";
    }

    return yaml;
}
