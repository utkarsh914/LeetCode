
class Solution {
public:
	int maxRepeating(string s, string word) {
		int c=0;
		string temp = word;
		while (s.find(temp) != string::npos)
			c++, temp+=word;
		return c;
	}
};