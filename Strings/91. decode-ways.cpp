// https://leetcode.com/problems/decode-ways/

/*
A message containing letters from A-Z can be encoded into numbers using the following mapping:

'A' -> "1"
'B' -> "2"
...
'Z' -> "26"
To decode an encoded message, all the digits must be mapped back into letters using the reverse of the mapping above (there may be multiple ways). For example, "111" can have each of its "1"s be mapped into 'A's to make "AAA", or it could be mapped to "11" and "1" ('K' and 'A' respectively) to make "KA". Note that "06" cannot be mapped into 'F' since "6" is different from "06".

Given a non-empty string num containing only digits, return the number of ways to decode it.

The answer is guaranteed to fit in a 32-bit integer.

 

Example 1:

Input: s = "12"
Output: 2
Explanation: "12" could be decoded as "AB" (1 2) or "L" (12).
Example 2:

Input: s = "226"
Output: 3
Explanation: "226" could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).
*/

class Solution {
	
	int dp[101];

	int count(string& s, int n=0) {
		if (n>=s.length()) return 1;
		if (dp[n]!=-1) return dp[n];
		if (s[n] == '0') return 0;
		int ans = count(s, n+1);
		if (n+1<s.length() && stoi(s.substr(n,2))<27)
			ans += count(s, n+2);
		return dp[n]=ans;
	}

public:
	int numDecodings(string& s) {
		memset(dp, -1, sizeof(dp));
		return count(s, 0);
	}
};