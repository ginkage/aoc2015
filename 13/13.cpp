#include "../lib.hpp"

unordered_map<uint16_t, long> dist;

uint16_t rehash(uint16_t from, uint16_t to) {
    return (from << 8) + to;
}

int main() {
    ifstream cin("input.txt");
    const regex linerex("(.*) would (.*) (.*) happiness units by sitting next to (.*).");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 5) {
            int name = remap(linematch[1].str());
            int sign = linematch[2].str() == "gain" ? 1 : -1;
            int pts = stoi(linematch[3].str()) * sign;
            int next = remap(linematch[4].str());
            dist[rehash(name, next)] = pts;
        }        
    }

    vector<int> order;
    int n = names.size();
    long result = 0;
    for (int i = 0; i < n; i++)
        order.push_back(i);
    order.push_back(n++);

    do {
        int prev = order[n-1], cur;
        long res = 0;
        for (int i = 0; i < n; i++) {
            cur = order[i];
            res += dist[rehash(cur,prev)] + dist[rehash(prev, cur)];
            prev = cur;
        }
        result = max(result, res);
    } while (next_permutation(order.begin(), order.end()));
    
    cout << result << endl;
    return 0;
}