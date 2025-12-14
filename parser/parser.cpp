#include "parser.h"

map<string, map<string, ParsedValue>>
parse(const vector<Token>& tokens) {

    map<string, map<string, ParsedValue>> config;
    string currentSection = "global";

    for (int i = 0; i < tokens.size(); i++) {

        if (tokens[i].type == SECTION) {
            currentSection = tokens[i].text;
        }

        if (tokens[i].type == KEY) {
            if (i + 2 < tokens.size() &&
                tokens[i + 1].type == ASSIGN &&
                tokens[i + 2].type == VALUE) {

                config[currentSection][tokens[i].text] =
                    {tokens[i + 2].text, tokens[i].line};
            }
        }
    }

    return config;
}
