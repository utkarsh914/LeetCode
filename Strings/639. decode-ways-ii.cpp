
// https://leetcode.com/problems/decode-ways-ii/submissions/

/*
A message containing letters from A-Z is being encoded to numbers using the following mapping way:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Beyond that, now the encoded string can also contain the character '*',
which can be treated as one of the numbers from 1 to 9.
Given the encoded message containing digits and the character '*', return the total number of ways to decode it.
Also, since the answer may be very large, you should return the output mod 109 + 7.

Example 1:
Input: "*"
Output: 9
Explanation: The encoded message can be decoded to the string: "A", "B", "C", "D", "E", "F", "G", "H", "I".
Example 2:
Input: "1*"
Output: 9 + 9 = 18
Note:
The length of the input string will fit in range [1, 105].
The input string will only contain the character '*' and digits '0' - '9'.
*/

class Solution {
	
	vector<int> dp;
	int M=1000000007;

	int count(string& s, int n=0) {
		if (n>=s.length()) return 1;
		if (dp[n]!=-1) return dp[n];
		if (s[n] == '0') return 0;
		
		long long int ans = count(s, n+1);
		if (s[n] == '*') ans = (9*ans) % M;

		// if next char doesn't exist, return ans
		if (n+1 == s.length())
			return dp[n] = (ans % M);

		// if next char exists
		int nextCount = count(s, n+2);

		// if curr char is *
		if (s[n]=='*') {
			if (s[n+1]=='*') {
				ans += (15*count(s, n+2)) % M;
			}
			else if (s[n+1]!='*') {
				if (s[n+1]<'7') ans += (2*nextCount) % M;
				else ans += (1*nextCount) % M;
			}
		}
		// if curr char is not *
		else if (s[n] != '*') {
			if (s[n+1]=='*'){
				if (s[n]=='1') ans += (9*nextCount) % M;
				else if (s[n]=='2') ans += (6*nextCount) % M;
			}
			else if (s[n+1]!='*' && stoi(s.substr(n,2))<27) {
				ans += (nextCount) % M;
			}
		}
		
		return dp[n] = (ans % M);
	}

public:
	int numDecodings(string& s) {
		dp.resize(s.length()+1, -1);
		return count(s, 0);
	}
};