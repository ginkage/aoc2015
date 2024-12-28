#include "../lib.hpp"

int main() {
    int target_row = 2978, target_col = 3083;
    uint64_t num = 20151125;
    int offset = target_col;
    for (int d = 0; d < target_row + target_col - 1; d++)
        offset += d;
    for (int i = 1; i < offset; i++)
        num = (num * 252533) % 33554393;
    cout << num << endl;
    return 0;
}

