// https://leetcode.com/problems/maximum-non-negative-product-in-a-matrix/

/*
You are given a rows x cols matrix grid. Initially,
you are located at the top-left corner (0, 0), and in each step,
you can only move right or down in the matrix.

Among all possible paths starting from the top-left corner (0, 0)
and ending in the bottom-right corner (rows - 1, cols - 1),
find the path with the maximum non-negative product.
The product of a path is the product of all integers
in the grid cells visited along the path.

Return the maximum non-negative product modulo 109 + 7.
If the maximum product is negative return -1.

Notice that the modulo is performed after getting the maximum product.

Example 1:

Input: grid = [[-1,-2,-3],
               [-2,-3,-3],
               [-3,-3,-2]]
Output: -1
Explanation: It's not possible to get non-negative product in the path from (0, 0) to (2, 2), so return -1.
Example 2:

Input: grid = [[1,-2,1],
               [1,-2,1],
               [3,-4,1]]
Output: 8
Explanation: Maximum non-negative product is in bold (1 * 1 * -2 * -4 * 1 = 8).
*/







/*
Use Dynamic programming.
Keep the highest value and lowest value you can achieve up to a point.
*/
class Solution {
public:
	int maxProductPath(vector<vector<int>>& G) {
		int R = G.size(), C = G[0].size();
		vector<vector<array<long,2>>> dp(R, vector<array<long,2>> (C));
		
		dp[0][0] = {G[0][0], G[0][0]};
		// first row
		for (int j = 1; j < C; j++) {
			dp[0][j] = {dp[0][j-1][0] * long(G[0][j]), dp[0][j-1][1] * long(G[0][j])};
		}
		// first col
		for (int i = 1; i < R; i++) {
			dp[i][0] = {dp[i-1][0][0] * long(G[i][0]), dp[i-1][0][1] * long(G[i][0])};
		}

		for (int i = 1; i < R; i++) {
			for (int j = 1; j < C; j++) {
				long cur = G[i][j];
				long a = cur * dp[i-1][j][0], b = cur * dp[i-1][j][1];
				long c = cur * dp[i][j-1][0], d = cur * dp[i][j-1][1];
				dp[i][j] = { min({a,b,c,d}), max({a,b,c,d}) };
			}
		}

		long ans =  dp[R-1][C-1][1] % 1000000007L;
		return ans < 0 ? -1 : ans;
	}
};