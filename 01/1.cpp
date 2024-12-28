#include <iostream>

using namespace std;

int main() {
	string s;
	cin >> s;

	int result = 0, pos = 1;
	for (const char &c : s) {
		if (c == '(') result++;
		else if (c == ')') result--;
		if (result == -1)
			cout << pos << endl;
		pos++;
	}

	cout << result << endl;

	return 0;
}
