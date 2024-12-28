#include "../lib.hpp"

struct item_t {
    int cost, damage, armor;
};

vector<item_t> weapons = {
    {  8, 4, 0 },
    { 10, 5, 0 },
    { 25, 6, 0 },
    { 40, 7, 0 },
    { 74, 8, 0 }
};

vector<item_t> armors = {
    {  13, 0, 1 },
    {  31, 0, 2 },
    {  53, 0, 3 },
    {  75, 0, 4 },
    { 102, 0, 5 }
};

vector<item_t> rings = {
    {  25, 1, 0 },
    {  50, 2, 0 },
    { 100, 3, 0 },
    {  20, 0, 1 },
    {  40, 0, 2 },
    {  80, 0, 3 }
};

void apply(item_t &st, item_t &it) {
    st.cost += it.cost;
    st.damage += it.damage;
    st.armor += it.armor;
}

int result_a = -1, result_b = -1;

void simulate(int i, int j, int r, int l) {
    item_t stats = { 0, 0, 0 };
    apply(stats, weapons[i]);
    if (j < armors.size())
        apply(stats, armors[j]);
    if (r < rings.size())
        apply(stats, rings[r]);
    if (l < rings.size())
        apply(stats, rings[l]);

    int boss_hp = 100, player_hp = 100;
    int boss_dmg = 8, player_dmg = stats.damage;
    int boss_arm = 2, player_arm = stats.armor;
    int cost = stats.cost;

    bool player_turn = true;
    while (boss_hp > 0 && player_hp > 0) {
        if (player_turn)
            boss_hp -= max(player_dmg - boss_arm, 1);
        else
            player_hp -= max(boss_dmg - player_arm, 1);
        player_turn = !player_turn;
    }

    if (player_hp > 0 && (result_a < 0 || result_a > stats.cost))
        result_a = stats.cost;
    if (boss_hp > 0)
        result_b = max(result_b, stats.cost);
}

int main() {
    for (int i = 0; i < weapons.size(); i++)
        for (int j = 0; j <= armors.size(); j++)
            for (int r = 0; r <= rings.size(); r++)
                for (int l = r; l <= rings.size(); l++)
                    if (l != r || l == rings.size())
                        simulate(i, j, r, l);
    cout << result_a << ' ' << result_b << endl;
    return 0;
}

