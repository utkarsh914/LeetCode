// https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/


class Solution {
public:
	int minAddToMakeValid(string& s) {
		int stk = 0, ans = 0;
		for (char c : s) {
			if (c == '(') stk++;
			else {
				if (stk == 0) ans++;
				else stk--;
			}
		}
		return ans + stk;
	}
};