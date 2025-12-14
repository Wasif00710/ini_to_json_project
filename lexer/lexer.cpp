#include "lexer.h"
#include <bits/stdc++.h>

using namespace std;

vector<Token> tokenize(const string& filename) {
    vector<Token> tokens;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        if (line.length() == 0) continue;

        // -------- SECTION [name] --------
        if (line[0] == '[') {
            string sectionName = "";

            // start from index 1, skip '[' and stop before ']'
            for (int i = 1; i < line.length() - 1; i++) {
                sectionName += line[i];
            }

            tokens.push_back({SECTION, sectionName});
        }

        // -------- KEY = VALUE --------
        else {
            string key = "";
            string value = "";
            bool foundEqual = false;

            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '=') {
                    foundEqual = true;
                    continue;
                }

                if (!foundEqual)
                    key += line[i];
                else
                    value += line[i];
            }

            if (foundEqual) {
                tokens.push_back({KEY, key});
                tokens.push_back({ASSIGN, "="});
                tokens.push_back({VALUE, value});
            }
        }

        tokens.push_back({NEWLINE, "\\n"});
    }

    return tokens;
}

