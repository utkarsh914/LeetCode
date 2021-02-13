// https://leetcode.com/problems/smallest-string-with-a-given-numeric-value/

class Solution {
public:
	string getSmallestString(int n, int k) {
		string s(n, 'a');
		k -= n;
		for (int i=n-1; i>=0 && k>0; i--) {
			int increment = min(25, k);
			s[i] += increment;
			k -= increment;
		}
		return s;
	}
};