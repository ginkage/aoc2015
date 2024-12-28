#include "../lib.hpp"

int main() {
    int total = 0;
    vector<int> package;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        package.push_back(stoi(s));
        total += package.back();
    }

    int third = total / 3, fourth = total / 4, best_room = package.size();
    long result = -1;
    for (uint32_t mask = 0; mask < (1 << package.size()); mask++) {
        int sum = 0, num = 0;
        for (int i = 0; i < package.size(); i++)
            if (mask & (1 << i)) {
                sum += package[i];
                num++;
            }
        if (sum == fourth) {
            long qe = 1;
            for (int i = 0; i < package.size(); i++)
                if (mask & (1 << i))
                    qe *= package[i];

            if (best_room > num) {
                best_room = num;
                result = -1;
            }
            if (best_room == num && (result < 0 || result > qe))
                result = qe;
        }
    }
    cout << result << endl;

    return 0;
}

