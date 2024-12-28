#include "../lib.hpp"

int main()
{
    vector<string> grid; /* = {
        ".#.#.#",
        "...##.",
        "#....#",
        "..#...",
        "#.#..#",
        "####.."
    };*/
    int m, n;

    ifstream cin("input.txt");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        grid.push_back(s);
    }

    m = grid.size();
    n = grid[0].size();
    
    vector<string> next(m, string(n, '.'));
    for (int t = 0; t < 100; t++) {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                int alive = 0;
                for (int di = -1; di <= 1; di++)
                    for (int dj = -1; dj <= 1; dj++) {
                        int ni = i + di, nj = j + dj;
                        if (ni >= 0 && nj >= 0 && ni < m && nj < n && (ni != i || nj != j) && grid[ni][nj] == '#')
                            alive++;
                    }
                next[i][j] = ((alive == 3) || (alive == 2 && grid[i][j] == '#')) ? '#' : '.';
            }
        /*
        for (string s : next)
           cout << s << endl;
        cout << endl;
        */
        next[0][0] = '#';
        next[0][n-1] = '#';
        next[m-1][0] = '#';
        next[m-1][n-1] = '#';
        swap(grid, next);
    }
    
    int result = 0;
    for (int i= 0; i < m; i++)
        for (int j = 0; j < n; j++)
            result += grid[i][j] == '#';
    cout << result << endl;

	return 0;
}