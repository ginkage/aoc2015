#include "../lib.hpp"

struct boss_t {
    int hp, damage;
};

struct player_t {
    int hp, mana, spent;
};

struct effect_t {
    int shield_time, poison_time, recharge_time;
};

int result = -1;

void handle_win(int spent) {
    if (result < 0 || result > spent)
        result = spent;
}

bool can_spend(player_t &player, int mana, player_t &np) {
    if (player.mana >= mana) {
        np = player;
        np.mana -= mana;
        np.spent += mana;
        return true;
    }
    return false;
}

void simulate(boss_t boss, player_t player, effect_t effect, bool player_turn) {
    if (result > 0 && player.spent > result)
        return;

    if (player_turn) {
        player.hp--;
        if (player.hp <= 0)
            return;
    }

    // Apply effects
    int player_armor = 0;
    if (effect.shield_time > 0) {
        player_armor = 7;
        effect.shield_time--;
    }

    if (effect.poison_time > 0) {
        boss.hp -= 3;
        effect.poison_time--;

        if (boss.hp <= 0) {
            handle_win(player.spent);
            return;
        }
    }

    if (effect.recharge_time > 0) {
        player.mana += 101;
        effect.recharge_time--;
    }

    if (player_turn) {
        // Cast spell
        player_t np;

        if (can_spend(player, 53, np)) { // Magic Missile
            boss_t nb = boss;
            nb.hp -= 4;
            if (nb.hp <= 0)
                handle_win(np.spent);
            else
                simulate(nb, np, effect, false);
        }

        if (can_spend(player, 73, np)) { // Drain
            boss_t nb = boss;
            nb.hp -= 2;
            np.hp += 2;
            if (nb.hp <= 0)
                handle_win(np.spent);
            else
                simulate(nb, np, effect, false);
        }

        if (effect.shield_time == 0 && can_spend(player, 113, np)) { // Shield
            effect_t ne = effect;
            ne.shield_time = 6;
            simulate(boss, np, ne, false);
        }

        if (effect.poison_time == 0 && can_spend(player, 173, np)) { // Poison
            effect_t ne = effect;
            ne.poison_time = 6;
            simulate(boss, np, ne, false);
        }

        if (effect.recharge_time == 0 && can_spend(player, 229, np)) { // Recharge
            effect_t ne = effect;
            ne.recharge_time = 5;
            simulate(boss, np, ne, false);
        }
    }
    else {
        // Boss attack
        player.hp -= max(boss.damage - player_armor, 1);
        if (player.hp > 0)
            simulate(boss, player, effect, true);
    }
}

int main() {
    boss_t boss { 51, 9 };
    player_t player { 50, 500, 0 };
    effect_t effects = { 0, 0, 0 };
    simulate(boss, player, effects, true);
    cout << result << endl;
    return 0;
}

