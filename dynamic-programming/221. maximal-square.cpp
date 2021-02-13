/*
https://leetcode.com/problems/maximal-square/

Given an m x n binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.

*/


class Solution {
public:
	int maximalSquare(vector<vector<char>>& M);
};

int Solution::maximalSquare(vector<vector<char>>& M) {
	int R = M.size();
	if (!R) return 0;
	int C = M[0].size();
	if (!C) return 0;

	int dp[R][C];
	int ans = 0; // dimension of square
	for (int i=0; i<R; i++) {
		for (int j=0; j<C; j++) {
			if (i==0 or j==0) dp[i][j]=M[i][j]-'0';
			else if (M[i][j]=='0') dp[i][j]=0;
			else dp[i][j] = min(dp[i-1][j-1], min(dp[i][j-1],dp[i-1][j])) + M[i][j]-'0';
			ans = max(ans, dp[i][j]);
		}
	}
	// for (int i=0; i<R; i++) {
	// 	for (int j=0; j<C; j++) cout<<dp[i][j]<<" ";
	// 	cout<<"\n";
	// }
	// return area
	return ans*ans;
}