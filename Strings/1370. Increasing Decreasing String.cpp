// https://leetcode.com/problems/increasing-decreasing-string/

class Solution {
public:
	string sortString(string& s) {
		int f[26] = {};
		for (char& c : s) {
			f[c-'a']++;
		}

		string ans;
		while (ans.size() < s.size()) {
			// inc
			for (int i = 0; i < 26; i++)
				if (f[i] > 0) ans += char(i+'a'), f[i]--;
			// dec
			for (int i = 25; i >= 0; i--)
				if (f[i] > 0) ans += char(i+'a'), f[i]--;
		}

		return ans;
	}
};