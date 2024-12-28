#include "../lib.hpp"

enum cmd_t {
    cmd_on,
    cmd_off,
    cmd_toggle
};

struct instr_t {
    cmd_t cmd;
    int i1, j1, i2, j2;
};

int main() {
    ifstream cin("input.txt");
    const regex linerex("(.*) (\\d+),(\\d+) through (\\d+),(\\d+)");
    vector<instr_t> instr;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 6) {
            string cmd = linematch[1].str();
            int i1 = stoi(linematch[2].str());
            int j1 = stoi(linematch[3].str());
            int i2 = stoi(linematch[4].str());
            int j2 = stoi(linematch[5].str());
            instr.push_back(instr_t { .cmd = (cmd == "turn on" ? cmd_on : (cmd == "turn off" ? cmd_off : cmd_toggle)),
                .i1 = i1, .j1 = j1, .i2 = i2, .j2 = j2 });
        }
    }

    int result_a = 0;
    long result_b = 0;
    for (int i = 0; i < 1000; i++)
        for (int j = 0; j < 1000; j++) {
            bool state = false;
            long level = 0;
            for (auto &it : instr) {
                if (i >= it.i1 && i <= it.i2 && j >= it.j1 && j <= it.j2) {
                    if (it.cmd == cmd_on) {
                        state = true;
                        level++;
                    }
                    else if (it.cmd == cmd_off) {
                        state = false;
                        level = max(level - 1, 0l);
                    }
                    else {
                        state = !state;
                        level += 2;
                    }
                }
            }
            if (state)
                result_a++;
            result_b += level;
        }
    cout << result_a << ' ' << result_b << endl;

    return 0;
}
