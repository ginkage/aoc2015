#include "../lib.hpp"

struct ingr_t {
    long capacity;
    long durability;
    long flavor;
    long texture;
    long calories;
};

vector<ingr_t> ingr;

long result = 0;

void iterate(int i, int spoons, ingr_t total) {
    if (spoons < 0) return;

    ingr_t &it = ingr[i];
    if (i == ingr.size() - 1) {
        total.capacity += it.capacity * spoons;
        total.durability += it.durability * spoons;
        total.flavor += it.flavor * spoons;
        total.texture += it.texture * spoons;
        total.calories += it.calories * spoons;
        if (total.capacity > 0 && total.durability > 0 && total.flavor > 0 && total.texture > 0 && total.calories == 500) {
            long score = total.capacity * total.durability * total.flavor * total.texture;
            result = max(result, score);
        }
    }
    else {
        iterate(i + 1, spoons, total);
        for (int s = 1; s <= spoons; s++) {
            total.capacity += it.capacity;
            total.durability += it.durability;
            total.flavor += it.flavor;
            total.texture += it.texture;
            total.calories += it.calories;
            iterate(i + 1, spoons - s, total);
        }
    }
}

int main()
{
    ifstream cin("input.txt");
    const regex linerex("(.*): capacity (.*), durability (.*), flavor (.*), texture (.*), calories (.*)");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 7) {
            string name = linematch[1].str();
            ingr.push_back(ingr_t {
                .capacity = stol(linematch[2].str()),
                .durability = stol(linematch[3].str()),
                .flavor = stol(linematch[4].str()),
                .texture = stol(linematch[5].str()),
                .calories = stol(linematch[6].str()) });
        }
    }

    ingr_t total = { 0, 0, 0, 0, 0 };
    iterate(0, 100, total);
    cout << result << endl;

    return 0;
}