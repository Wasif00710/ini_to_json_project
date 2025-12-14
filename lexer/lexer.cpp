#include "lexer.h"

vector<Token> tokenize(const string &filename)
{
    vector<Token> tokens;
    ifstream file(filename);

    string line;
    int lineNo = 1;

    while (getline(file, line))
    {
        if (line.size() == 0)
        {
            lineNo++;
            continue;
        }

        // Section
        if (line[0] == '[')
        {
            string section = "";
            for (int i = 1; i < line.size() - 1; i++)
                section += line[i];

            tokens.push_back({SECTION, section, lineNo});
        }
        // key=value
        else
        {
            string key = "", value = "";
            bool foundEq = false;

            for (char c : line)
            {

                // ignore spaces
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
