#include <iostream>
#include <fstream>
#include <map>
using namespace std;

int main() {
    ifstream file("config.ini");

    if (!file) {
        cout << "File not found!" << endl;
        return 0;
    }

    map<string, map<string, string>> data;
    string line, section = "global";

    while (getline(file, line)) {

        // ignore empty lines
        if (line.size() == 0) continue;

        // section
        if (line[0] == '[') {
            section = line.substr(1, line.size() - 2);
        }
        // key=value
        else {
            int pos = line.find('=');
            if (pos != string::npos) {
                string key = line.substr(0, pos);
                string value = line.substr(pos + 1);
                data[section][key] = value;
            }
        }
    }

    // Print JSON
    cout << "{\n";
    for (auto sec : data) {
        cout << "  \"" << sec.first << "\": {\n";
        for (auto kv : sec.second) {
            cout << "    \"" << kv.first << "\": \"" << kv.second << "\"\n";
        }
        cout << "  }\n";
    }
    cout << "}\n";

    return 0;
}
