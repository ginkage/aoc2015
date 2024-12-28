#include "../lib.hpp"

vector<int> cap;

int result = 0, kbest = 1000000;

void iterate(int i, int left, int k) {
    if (left < 0) return;
    if (left == 0) {
        if (k == kbest)
            result++;
        else if (k < kbest) {
            kbest = k;
            result = 1;
        }
        return;
    }
    if (i >= cap.size()) return;
    iterate(i+1, left, k);
    iterate(i+1, left - cap[i], k + 1);
}

int main()
{
    ifstream cin("input.txt");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin || !s.size()) break;
        cap.push_back(stoi(s));
    }
    iterate(0, 150, 0);
    cout << result << endl;
    return 0;
}