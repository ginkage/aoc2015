#include "../lib.hpp"

int main() {
    long result_a = 0, result_b = 0;
    ifstream cin("input.txt");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        int len = s.size(), skip = 2, bloat = 2;
        for (int i = 1; i < len - 1; i++) {
            if (s[i] == '\\') {
                if (s[i+1] == 'x') {
                    i += 3;
                    skip += 3;
                }
                else {
                    i++;
                    skip++;
                }
            }
        }
        for (char c : s)
            if (c == '\\' || c == '\"')
                bloat++;
        result_a += skip;
        result_b += bloat;
    }
    
    cout << result_a << ' ' << result_b << endl;
    return 0;
}
