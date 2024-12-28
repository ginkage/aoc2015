#include "../lib.hpp"

unordered_map<string, int> sue = {
    { "children", 3 },
    { "cats", 7 },
    { "samoyeds", 2 },
    { "pomeranians", 3 },
    { "akitas", 0 },
    { "vizslas", 0 },
    { "goldfish", 5 },
    { "trees", 3 },
    { "cars", 2 },
    { "perfumes", 1 }
};

int main()
{
    ifstream cin("input.txt");
    const regex linerex("Sue (\\d+): (.*)");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 3) {
            bool good = true;
            int num = stoi(linematch[1].str());
            for (string v : split_s(linematch[2].str(), ", ")) {
                auto t = split_s(v, ": ");
                string key = t[0];
                int val = stoi(t[1]);
                if (key == "cats" || key == "trees") {
                    if (val <= sue[key])
                        good = false;
                }
                else if (key == "pomeranians" || key == "goldfish") {
                    if (val >= sue[key])
                        good = false;
                }
                else if (sue[key] != val)
                    good = false;
            }
            if (good)
                cout << num << endl;
        }
    }
    
    return 0;
}