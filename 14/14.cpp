#include "../lib.hpp"

int main() {
    ifstream cin("input.txt");
    long result = 0;
    const regex linerex("(.*) can fly (.*) km/s for (.*) seconds, but then must rest for (.*) seconds.");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 5) {
            string name = linematch[1].str();
            long speed = stol(linematch[2].str());
            int duration = stoi(linematch[3].str());
            int rest = stoi(linematch[4].str());
            
            int seg = duration + rest;
            int wh = 2503 / seg;
            int re = 2503 % seg;
            long dist = (wh * duration + min(re, duration)) * speed;
            result = max(result, dist);
        }
    }

    cout << result << endl;
    return 0;
}