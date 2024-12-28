#include "../lib.hpp"

struct node_t {
    unordered_map<char, unique_ptr<node_t>> child;
    unordered_set<string> subst;
};
node_t root;

int main() {
    ifstream cin("input.txt");
    const regex linerex("(.*) => (.*)");
    string s;
    while (true) {
        getline(cin, s);
        if (!s.size()) break;
        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 3) {
            string from = linematch[1].str();
            string to = linematch[2].str();

            node_t *node = &root;
            for (char c : from) {
                if (!node->child[c].get())
                    node->child[c] = make_unique<node_t>();
                node = node->child[c].get();
            }
            node->subst.insert(to);
        }
    }

    getline(cin, s);
    unordered_set<string> to;
    for (int i = 0; i < s.size(); i++) {
        node_t *node = &root;
        for (int j = i; j < s.size(); j++) {
            auto it = node->child.find(s[j]);
            if (it == node->child.end()) break;
            node = it->second.get();
            if (!node->subst.empty()) {
                string prefix = s.substr(0, i);
                string suffix = s.substr(j + 1, s.size() - j - 1);
                for (const string &ss : node->subst)
                    to.insert(prefix + ss + suffix);
            }
        }
    }
    cout << to.size() << endl;

	return 0;
}