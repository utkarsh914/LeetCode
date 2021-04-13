// https://leetcode.com/problems/longest-increasing-path-in-a-matrix/

/*
Given an m x n integers matrix, return the length of the longest increasing path in matrix.

From each cell, you can either move in four directions: left, right, up, or down. You may not move diagonally or move outside the boundary (i.e., wrap-around is not allowed).

 

Example 1:


Input: matrix = [[9,9,4],[6,6,8],[2,1,1]]
Output: 4
Explanation: The longest increasing path is [1, 2, 6, 9].
Example 2:


Input: matrix = [[3,4,5],[3,2,6],[2,2,1]]
Output: 4
Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
Example 3:

Input: matrix = [[1]]
Output: 1
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 200
0 <= matrix[i][j] <= 231 - 1
*/


class Solution {
	vector<vector<int>> dp;
	int R,C;
public:
	int longestIncreasingPath(vector<vector<int>>& m) {
		R = m.size(), C = m[0].size();
		dp.resize(R+1, vector<int>(C+1, -1));
		int ans = 1;
		
		for (int i=0; i < R; i++)
			for (int j=0; j < C; j++)
				ans = max(ans, dfs(m, i, j));
		
		return ans;
	}
	
	int dfs(vector<vector<int>>& m, int r, int c) {
		if (dp[r][c] != -1)
			return dp[r][c];
		
		dp[r][c] = 1;
		int neighbour = 0;
		int dr[] = {-1, 0, 1, 0};
		int dc[] = {0, 1, 0, -1};
		
		for (int k=0; k < 4; k++) {
			int x = r + dr[k], y = c + dc[k];
			if (x<0 or x>=R or y<0 or y>=C or m[x][y] <= m[r][c])
				continue;
			neighbour = max(neighbour, dfs(m, x, y));
		}
		
		dp[r][c] += neighbour;
		return dp[r][c];
	}
};