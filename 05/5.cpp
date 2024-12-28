#include <map>
#include <iostream>
#include <string>

using namespace std;

int main() {
	int result = 0;
	while (!cin.eof()) {
		string s;
		cin >> s;

		if (!s.size()) break;
/*
		bool nice = true, dbl = false;
		int vowels = 0;
		for (int i = 0; i < s.size(); i++) {
			const char c = s[i];
			if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
				vowels++;
			if (i) {
				const char p = s[i-1];
				if ((p == 'a' && c == 'b') || (p == 'c' && c == 'd') || (p == 'p' && c == 'q') || (p == 'x' && c == 'y'))
					nice = false;
				if (p == c)
					dbl = true;
			}
		}
		if (!dbl || vowels < 3) nice = false;
*/
		bool ovo = false, pp = false;
		map<short, int> pos;
		for (int i = 0; i < s.size(); i++) {
			const char c = s[i];

			if (i) {
				short p = (s[i-1] << 8) + c;
				if (pos.find(p) == pos.end())
					pos[p] = i;
				else if (i - pos[p] > 1)
					pp = true;
			}

			if (i > 1) {
				const char p = s[i-2];
				if (p == c)
					ovo = true;
			}
		}

		if (ovo && pp) {
			cout << s << endl;
			result++;
		}
	}
	cout << result << endl;
	return 0;
}
