// https://leetcode.com/problems/longest-palindromic-substring/

/*
Given a string s, return the longest palindromic substring in s.

Example 1:

Input: s = "babad"
Output: "bab"
Note: "aba" is also a valid answer.
*/


class Solution {
public:
	string longestPalindrome(string& s) {
		int l = s.length();
		if (l == 0) return "";

		bool dp[l][l];

		// for substring of length k
		for (int k = 1; k <= l; k++) {
			for (int i = 0, j = k-1; j < l; i++, j++) {
				if (k == 1) dp[i][j] = true;
				else if (k == 2) dp[i][j] = (s[i] == s[j]);
				else {
					if (s[i] == s[j]) dp[i][j] = dp[i+1][j-1];
					else dp[i][j] = false;
				}
			}
		}

		int maxLen = 0; string ans;

		for (int i = 0; i < l; i++) {
			for (int j = i; j < l; j++) {
				if (dp[i][j] and j-i+1 > maxLen) {
					maxLen = j-i+1;
					ans = s.substr(i, maxLen);
				}
			}
		}

		return ans;
	}
};








string longestPalindrome(string& s) {
	int n = s.size();
	int start = 0, maxLen = 1;

	for (int i = 0; i < n; ) {
		int x = i-1, y = i+1;
		while (y < n && s[y] == s[i])
			y++;
		i = y;
		while (x >= 0 && y < n && s[x] == s[y])
			x--, y++;
		if (y-x-1 > maxLen)
			start = x+1, maxLen = y-x-1;
	}

	return s.substr(start, maxLen);
}