// https://leetcode.com/problems/remove-k-digits/

// similar to: 1673. find-the-most-competitive-subsequence

class Solution {
public:
	string removeKdigits(string num, int k) {
		string s; // operate on it as stack
		for (char d: num) {
			while (!s.empty() && s.back()>d && k>0) {
				k--;
				s.pop_back();
			}
			s.push_back(d);
		}
		while (!s.empty() && k>0) {
			k--;
			s.pop_back();
		}
		while (!s.empty() && s.front()=='0')
			s.erase(s.begin());
		return s.empty() ? "0" : s;
	}
};