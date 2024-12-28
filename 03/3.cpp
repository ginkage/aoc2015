#include <iostream>
#include <map>

using namespace std;

int main() {
	map<pair<int, int>, int> grid;
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	grid[make_pair(x1, y1)]++;
	bool turn = true;
	while (!cin.eof()) {
		int &x = turn ? x1 : x2;
		int &y = turn ? y1 : y2;
		switch (cin.get()) {
			case '^': y++; break;
			case 'v': y--; break;
			case '<': x--; break;
			case '>': x++; break;
			default:
				  cout << grid.size() << endl;
				  break;
		}
		turn = !turn;
		grid[make_pair(x, y)]++;
	}
	return 0;
}
