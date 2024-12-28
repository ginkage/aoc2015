#include "../lib.hpp"

uint64_t eval(int id);

struct val_t {
    bool im;
    uint64_t val;
    
    val_t(const string &s) {
        if (isdigit(s[0])) {
            im = true;
            val = stoi(s);
        }
        else {
            im = false;
            val = remap(s);
        }
    }
    
    val_t() {}

    uint64_t get() {
        return im ? val : eval(val);
    }
};

enum op_t {
    op_store,
    op_and,
    op_or,
    op_lshift,
    op_rshift,
    op_not
};

struct gate_t {
    op_t op;
    val_t v1, v2;
};

unordered_map<op_t, function<uint64_t(gate_t&)>> ops = {
    { op_store, [](gate_t &g) { return g.v1.get(); } },
    { op_and, [](gate_t &g) { return g.v1.get() & g.v2.get(); } },
    { op_or, [](gate_t &g) { return g.v1.get() | g.v2.get(); } },
    { op_lshift, [](gate_t &g) { return g.v1.get() << g.v2.get(); } },
    { op_rshift, [](gate_t &g) { return g.v1.get() >> g.v2.get(); } },
    { op_not, [](gate_t &g) { return ~g.v1.get(); } }
};

unordered_map<int, gate_t> wire;
unordered_map<int, uint64_t> cache;

uint64_t eval(int id) {
    auto it = cache.find(id);
    if (it != cache.end())
        return it->second;
    gate_t &g = wire[id];
    uint64_t res = ops[g.op](g);
    cache[id] = res;
    return res;
}

int main() {
    ifstream cin("input.txt");
    const regex linerex("(.*) -> (.*)");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 3) {
            auto ss = split_s(linematch[1].str(), " ");
            int out = remap(linematch[2].str());
            gate_t g;
            if (ss.size() == 1) {
                g.op = op_store;
                g.v1 = val_t(ss[0]);
            }
            else if (ss.size() == 2 && ss[0] == "NOT") {
                g.op = op_not;
                g.v1 = val_t(ss[1]);
            }
            else if (ss.size() == 3) {
                g.v1 = val_t(ss[0]);
                g.v2 = val_t(ss[2]);
                if (ss[1] == "AND")
                    g.op = op_and;
                else if (ss[1] == "OR")
                    g.op = op_or;
                else if (ss[1] == "RSHIFT")
                    g.op = op_rshift;
                else if (ss[1] == "LSHIFT")
                    g.op = op_lshift;
            }
            wire[out] = g;
        }
    }

    uint64_t res_a = eval(remap("a"));
    gate_t &b = wire[remap("b")];
    b.op = op_store;
    b.v1.im = true;
    b.v1.val = res_a;
    cache.clear();
    uint64_t res_b = eval(remap("a"));
    cout << res_a << ' ' << res_b << endl;

    return 0;
}