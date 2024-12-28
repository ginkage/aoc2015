#include "../lib.hpp"

struct deer_t {
    string name;
    int speed;
    int duration;
    int rest;
    int dist;
    int score;
};

static inline int dist(deer_t &d, int time) {
    int seg = d.duration + d.rest;
    int wh = time / seg;
    int re = time % seg;
    return (wh * d.duration + min(re, d.duration)) * d.speed;
}

int main()
{
    ifstream cin("input.txt");
    vector<deer_t> deer;
    const regex linerex("(.*) can fly (.*) km/s for (.*) seconds, but then must rest for (.*) seconds.");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin)
            break;
        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 5) {
            deer.push_back(deer_t {
                .name = linematch[1].str(),
                .speed = stoi(linematch[2].str()),
                .duration = stoi(linematch[3].str()),
                .rest = stoi(linematch[4].str()),
                .dist = 0,
                .score = 0 });
        }
    }
    
    int result = 0;
    for (int t = 1; t <= 2503; t++) {
        int mx = 0;
        for (deer_t &d : deer) {
            d.dist = dist(d, t);
            mx = max(mx, d.dist);
        }
        for (deer_t &d : deer) {
            if (d.dist == mx)
                d.score++;
            result = max(result, d.score);
        }
    }
    cout << result << endl;
    return 0;
}