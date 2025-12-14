#include "parser.h"

map<string, map<string, string>> parse(vector<Token> tokens) {

    map<string, map<string, string>> config;
    string currentSection = "global";

    for (int i = 0; i < tokens.size(); i++) {

        // -------- SECTION --------
        if (tokens[i].type == SECTION) {
            currentSection = tokens[i].text;
        }

        // -------- KEY = VALUE --------
        if (tokens[i].type == KEY) {
            string key = tokens[i].text;

            // next tokens: ASSIGN then VALUE
            if (i + 2 < tokens.size() &&
                tokens[i + 1].type == ASSIGN &&
                tokens[i + 2].type == VALUE) {

                string value = tokens[i + 2].text;
                config[currentSection][key] = value;
            }
        }
    }

    return config;
}
