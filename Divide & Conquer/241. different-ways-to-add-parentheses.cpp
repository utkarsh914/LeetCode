
// https://leetcode.com/problems/different-ways-to-add-parentheses/

class Solution {
	unordered_map<string, vector<int>> dp;
public:
	vector<int> diffWaysToCompute(string s) {
		if (dp.count(s)) return dp[s]; // check in dp

		vector<int> ans;
		bool pureNum = true;
		for (int i=0; i<s.length(); i++) {
			if (s[i]>='0' and s[i]<='9') continue; // if digit, continue
			pureNum = false;
			vector<int> left = diffWaysToCompute(s.substr(0,i));
			vector<int> right = diffWaysToCompute(s.substr(i+1, s.length()-i-1));
			for (int l:left)
				for (int r:right)
					if (s[i]=='+') ans.push_back(l+r);
					else if (s[i]=='-') ans.push_back(l-r);
					else if (s[i]=='*') ans.push_back(l*r);
		}
		if (pureNum)
			ans.push_back(stoi(s));
		
		return dp[s] = ans;
	}
};