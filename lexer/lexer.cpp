#include "lexer.h"

vector<Token> tokenize(const string &filename)
{
    vector<Token> tokens;
    ifstream file(filename);

    string line;
    int lineNo = 1;

    while (getline(file, line))
    {
        // remove leading spaces
        int idx = 0;
        while (idx < line.size() && (line[idx] == ' ' || line[idx] == '\t'))
            idx++;

        // skip empty or comment lines
        if (idx >= line.size() || line[idx] == ';' || line[idx] == '#')
        {
            lineNo++;
            continue;
        }

        // -------- SECTION --------
        if (line[idx] == '[' && line.back() == ']')
        {
            string section = "";
            for (int i = idx + 1; i < line.size() - 1; i++)
                section += line[i];

            tokens.push_back({SECTION, section, lineNo});
        }
        // -------- KEY = VALUE --------
        else
        {
            string key = "", value = "";
            bool foundEq = false;

            for (char c : line)
            {
                if (c == ' ' || c == '\t')
                    continue;

                if (c == '=')
                {
                    foundEq = true;
                    continue;
                }

                if (!foundEq)
                    key += c;
                else
                    value += c;
            }

            if (!foundEq)
            {
                cout << "Syntax Error (line " << lineNo
                     << "): Missing '='\n";
            }
            else
            {
                tokens.push_back({KEY, key, lineNo});
                tokens.push_back({ASSIGN, "=", lineNo});
                tokens.push_back({VALUE, value, lineNo});
            }
        }

        tokens.push_back({NEWLINE, "\\n", lineNo});
        lineNo++;
    }

    return tokens;
}
