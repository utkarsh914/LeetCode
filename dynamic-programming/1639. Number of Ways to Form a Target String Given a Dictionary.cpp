// https://leetcode.com/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/




/*
For each index i, store the frequency of each character in the ith row.

Use dynamic programing to calculate the number of ways
to get the target string using the frequency array,
*/
class Solution {
	int freq[1000][26] = {};
	int dp[1001][1001];
public:
	int numWays(vector<string>& words, string& s) {
		int M = words[0].size(), N = s.size();
		memset(dp, -1, sizeof(dp));
		
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < words.size(); j++) {
				char c = words[j][i];
				freq[i][c - 'a']++;
			}
		}
		
		return recur(M, 0, s, 0);
	}
	
	long recur(int M, int i, string& s, int j) {
		if (j == s.size()) return 1;
		if (i == M) return 0;
		if (dp[i][j] != -1) return dp[i][j];
		
		long x = freq[i][s[j] - 'a'];
		long take = x > 0 ? x * recur(M, i+1, s, j+1) : 0;
		long notTake = recur(M, i+1, s, j);
		return dp[i][j] = (take + notTake) % 1000000007L;
	}
};