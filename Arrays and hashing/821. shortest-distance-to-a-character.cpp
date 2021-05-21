// https://leetcode.com/problems/shortest-distance-to-a-character/

class Solution {
public:
	vector<int> shortestToChar(string& s, char c) {
		vector<int> ans(s.size());
		
		for (int i = s.size()-1, ind = INT_MAX; i >= 0; i--) {
			if (s[i] == c) ind = i;
			ans[i] = ind - i;
		}

		for (int i = 0, ind = INT_MIN/2; i < s.size(); i++) {
			if (s[i] == c) ind = i;
			ans[i] = min(ans[i], i - ind);
		}

		return ans;
	}
};