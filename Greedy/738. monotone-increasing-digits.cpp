// https://leetcode.com/problems/monotone-increasing-digits/

class Solution {
public:
	int monotoneIncreasingDigits(int N) {
		string s = to_string(N);
		int marker = -1;
		for (int i=s.size()-1; i>0; i--) {
			if (s[i] < s[i-1]) {
				marker = i;
				s[i-1]--;
			}
		}
		for (int i=marker; i!=-1 && i<s.size(); i++)
			s[i] = '9';
		return stoi(s);
	}
};