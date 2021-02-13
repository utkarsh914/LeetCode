// https://leetcode.com/problems/palindrome-partitioning-iv/

class Solution {
	short dp[2001][4];
	bool ispal[2001][2001];
public:
	bool checkPartitioning(string& s) {
		memset(dp, -1, sizeof(dp));
		// precalculate for checking if a substr is palindrome
		for (int len=1; len<=s.size(); len++) {
			for (int i=0, j=i+len-1; j<s.size(); i++, j++) {
				if (len == 1) ispal[i][j] = true;
				else if (len == 2) ispal[i][j] = s[i]==s[j];
				else {
					if (s[i]==s[j]) ispal[i][j] = ispal[i+1][j-1];
					else ispal[i][j] = false;
				}
			}
		}
		return check(s, 0, 3);
	}
	
	bool check(string& s, int start=0, int parts=3) {
		if (start > s.size()) return false;
		if (start == s.size() && parts==0) return true;
		if (parts == 0) return false;
		if (start == s.size()) return false;
		if (dp[start][parts] != -1) return dp[start][parts];
		
		for (int i=start; i<s.size(); i++) {
			if (ispal[start][i] && check(s, i+1, parts-1))
				return dp[start][parts] = true;
		}
		return dp[start][parts] = false;
	}

};