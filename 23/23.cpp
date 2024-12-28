#include "../lib.hpp"

enum op_t {
    op_hlf,
    op_tpl,
    op_inc,
    op_jmp,
    op_jie,
    op_jio
};

unordered_map<string, op_t> op_name = {
    { "hlf", op_hlf },
    { "tpl", op_tpl },
    { "inc", op_inc },
    { "jmp", op_jmp },
    { "jie", op_jie },
    { "jio", op_jio }
};

static uint32_t reg_a = 1, reg_b = 0, reg_jmp = 0;

struct cmd_t {
    op_t op;
    uint32_t *reg;
    int im;
};

unordered_map<op_t, function<void(cmd_t)>> ops = {
    { op_hlf, [](cmd_t c) { (*c.reg) /= 2; } },
    { op_tpl, [](cmd_t c) { (*c.reg) *= 3; } },
    { op_inc, [](cmd_t c) { (*c.reg)++; } },
    { op_jmp, [](cmd_t c) { reg_jmp = c.im; } },
    { op_jie, [](cmd_t c) { if ((*c.reg) % 2 == 0) reg_jmp = c.im; } },
    { op_jio, [](cmd_t c) { if ((*c.reg) == 1) reg_jmp = c.im; } }
};

int main() {
    const regex linerex2("(.*) (.*), (.*)");
    const regex linerex1("(.*) (.*)");
    vector<cmd_t> program;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        cmd_t cmd;
        smatch linematch;
        if (regex_match(s, linematch, linerex2) && linematch.size() == 4) {
            cmd.op = op_name[linematch[1].str()];
            cmd.reg = linematch[2].str() == "a" ? &reg_a : &reg_b;
            cmd.im = stoi(linematch[3].str());
        }
        else if (regex_match(s, linematch, linerex1) && linematch.size() == 3) {
            cmd.op = op_name[linematch[1].str()];
            if (cmd.op == op_jmp)
                cmd.im = stoi(linematch[2].str());
            else
                cmd.reg = linematch[2].str() == "a" ? &reg_a : &reg_b;
        }
        program.push_back(cmd);
    }

    uint32_t ptr = 0;
    while (ptr < program.size()) {
        reg_jmp = 1;
        cmd_t &cmd = program[ptr];
        ops[cmd.op](cmd);
        ptr += reg_jmp;
    }

    cout << reg_b << endl;

    return 0;
}

