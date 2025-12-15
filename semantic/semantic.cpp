#include "semantic.h"

// ---------- TYPE CHECKERS ----------

bool isInt(string s)
{
    if (s.empty()) return false;

    for (char c : s)
        if (c < '0' || c > '9')
            return false;

    return true;
}

bool isBool(string s)
{
    return (s == "true" || s == "false");
}

// ---------- LOAD SCHEMA  ----------

map<string, map<string, SchemaRule>>
loadSchema(const string &filename)
{
    ifstream file(filename);
    map<string, map<string, SchemaRule>> schema;

    string line, section = "";

    while (getline(file, line))
    {
        // remove spaces
        string cleaned = "";
        for (char c : line)
            if (c != ' ')
                cleaned += c;

        if (cleaned.empty() || cleaned[0] == ';' || cleaned[0] == '#')
            continue;

        // section [name]
        if (cleaned[0] == '[' && cleaned.back() == ']')
        {
            section = "";
            for (int i = 1; i < cleaned.size() - 1; i++)
                section += cleaned[i];
            continue;
        }

        // key=typeREQUIRED/OPTIONAL
        string key = "", type = "", req = "";
        bool seenEq = false, seenType = false;

        for (char c : cleaned)
        {
            if (c == '=')
            {
                seenEq = true;
                continue;
            }

            if (!seenEq)
                key += c;
            else if (!seenType && c >= 'a' && c <= 'z')
                type += c;
            else
            {
                seenType = true;
                req += c;
            }
        }

        if (key.empty() || type.empty())
            continue;

        SchemaRule rule;
        rule.type = type;
        rule.required = (req == "REQUIRED");

        schema[section][key] = rule;
    }

    return schema;
}

// ---------- SEMANTIC ANALYSIS (SMART MODE) ----------

map<string, map<string, TypedValue>>
analyze(map<string, map<string, ParsedValue>> config,
        map<string, map<string, SchemaRule>> schema)
{
    map<string, map<string, TypedValue>> result;

    for (auto sec : config)
    {
        // ignore sections not in schema
        if (schema.find(sec.first) == schema.end())
            continue;

        for (auto rule : schema[sec.first])
        {
            // missing key
            if (config[sec.first].find(rule.first) == config[sec.first].end())
            {
                if (rule.second.required)
                {
                    cout << "Semantic Error: Missing required key '"
                         << rule.first << "' in ["
                         << sec.first << "]\n";
                }
                continue;
            }

            auto pv = config[sec.first][rule.first];
            TypedValue tv;
            tv.line = pv.line;

            if (rule.second.type == "int" && isInt(pv.value))
            {
                tv.type = "int";
                tv.value = pv.value;
            }
            else if (rule.second.type == "bool" && isBool(pv.value))
            {
                tv.type = "bool";
                tv.value = pv.value;
            }
            else if (rule.second.type == "string")
            {
                tv.type = "string";
                tv.value = pv.value;
            }
            else
            {
                cout << "Type Error (line " << pv.line << "): "
                     << rule.first << " expected "
                     << rule.second.type << "\n";
                continue;
            }

            result[sec.first][rule.first] = tv;
        }
    }

    return result;
}
