#include "../lib.hpp"

int main()
{
	string s = "1322113";
	for (int k = 0; k <= 50; k++) {
	    stringstream ss;
	    for (int i = 0; i < s.size();) {
	        char c = s[i];
	        int count = 1;
	        for (int j = i + 1; j < s.size() && s[j] == c; j++)
	            count++;
	        ss << count << c;
	        i += count;
	    }
	    s = ss.str();
	    cout << s.size() << endl;
	}
	return 0;
}