#include "../lib.hpp"

unordered_map<uint16_t, long> dist;

uint16_t rehash(uint16_t from, uint16_t to) {
    return (from << 8) + to;
}

int main() {
    long result = 0;
    ifstream cin("input.txt");
    const regex linerex("(.*) to (.*) = (.*)");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 4) {
            int from = remap(linematch[1].str());
            int to = remap(linematch[2].str());
            long len = stol(linematch[3].str());
            dist[rehash(from, to)] = len;
            dist[rehash(to, from)] = len;
            // result += len;
        }
    }

    vector<int> order;
    int n = names.size();
    for (int i = 0; i < n; i++)
        order.push_back(i);
    do {
        long res = 0;
        for (int i = 1; i < n; i++)
            res += dist[rehash(order[i-1], order[i])];
        result = max(result, res);
    } while (next_permutation(order.begin(), order.end()));
    
    cout << result << endl;

    return 0;
}