#include "../lib.hpp"

static inline uint64_t count_mult(uint64_t num) {
    uint64_t hi = floor(sqrtf(num) + 0.5);
    unordered_set<uint64_t> mm;
    for (uint64_t mul = 1; mul <= hi && mul <= num; mul++)
        if (num % mul == 0) {
            mm.insert(mul);
            mm.insert(num / mul);
        }
    uint64_t res = 0;
    for (uint64_t t : mm)
        res += t;
    return res;
}

int main() {
    uint64_t target = 36000000;
    for (uint64_t house = 1; ; house++) {
        if (count_mult(house) * 10 >= target) {
            cout << house << endl;
            break;
        }
    }

    return 0;
}

