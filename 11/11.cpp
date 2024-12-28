#include "../lib.hpp"

int main()
{
	string s = "hxbxwxba";
	int cnt = 2;
	while (cnt) {
	    bool carry = true;
	    for (int j = s.size() - 1; j >= 0 && carry; j--) {
	        carry = (s[j] == 'z');
	        s[j] = carry ? 'a' : (s[j] + 1);
	    }
	    
	    for (int j = 0; j < s.size(); j++) {
	        char c = s[j];
	        if (c == 'i' || c == 'l' || c == 'o') {
	            s[j] = c + 1;
	            for (int k = j + 1; k < s.size(); k++)
	                s[k] = 'a';
	            break;
	        }
	    }
	    
	    char rep1 = 0, rep2 = 0;
	    for (int j = 0; j < s.size() - 1 && rep2 == 0; j++)
	        if (s[j+1] == s[j]) {
	            if (rep1 == 0)
	                rep1 = s[j];
	            else if (s[j] != rep1)
	                rep2 = s[j];
	        }
	    
	    bool three = false;
	    for (int j = 0; j < s.size() - 2 && !three; j++)
	        three = s[j+1] == s[j] + 1 && s[j+2] == s[j] + 2;
	    if (rep2 && three) {
	        cout << s << endl;
	        cnt--;
	    }
	}
	return 0;
}