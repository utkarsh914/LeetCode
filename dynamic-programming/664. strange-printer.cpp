// https://leetcode.com/problems/strange-printer/

/*
The problem is easier to solve if we decrease it to subproblems using Divide and Conquer.
base case:
if s contains only 1 character, 1 turn is needed
if s contains 2 characters, 1 turn is needed if they equal to each other, or else, 2 turns are needed
divide the problem:
we keep dividing s until the substring contains 1 or 2 characters (as the base case)
Take s = "abc" for example,

  abc
 /    \
a,bc ab,c (base case here)
conquer the subproblems:
turns s needed = min(turns one substring needed + turns the other needed) (since there are many ways to divide s, we pick the one needs minimum turns)
Please note that, if s = "aba", and we divide it into "a,ba", turns "aba" needed = turns "a" needed + turns "ba" needed - 1 (aaa => aba rather than a => ab => aba).

To avoid duplicate calculations, we implement the idea above using Bottom-up Dynamic Programming.
state: state[i][j] turns needed to print s[i .. j] (both inclusive)
aim state: state[0][n - 1] (n = s.length() - 1)
state transition:

state[i][i] = 1;
state[i][i + 1] = 1 if s[i] == s[i + 1]
state[i][i + 1] = 2 if s[i] != s[i + 1]
state[i][j] = min(state[i][k] + state[k + 1][j]) for i <= k <= j - 1
please note that, if s[i] equals to s[j] , state[i][j] should -1
*/

class Solution {
	// remove duplicate consecutive chars as they don't have any effect on result
	void preProcess(string& s) {
		std::regex re("(.)\\1*");
		s = std::regex_replace(s, re, "$1");
	}

public:
int strangePrinter(string& s) {
	preProcess(s); // not needed

	int l = s.length();
	if (l==0) return 0;

	int dp[l][l];
	// for one length
	for (int i=0; i<s.length(); i++)
		dp[i][i] = 1;
	// for two length
	for (int i=1; i<s.length(); i++)
		dp[i-1][i] = s[i-1]==s[i] ? 1 : 2;
	// for more lengths
	for (int len=3; len<=l; len++) {
		for (int i=0; i+len-1<l; i++) {
			int j = i+len-1;
			int temp = INT_MAX;
			for (int k=i; k<j; k++) {
				temp = min(temp, dp[i][k]+dp[k+1][j] );
			}
			dp[i][j] = temp;
			if (s[i]==s[j]) dp[i][j]--;
		}
	}

	return dp[0][l-1];

}};