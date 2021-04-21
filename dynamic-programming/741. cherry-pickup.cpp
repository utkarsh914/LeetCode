// https://leetcode.com/problems/cherry-pickup/

/*
You are given an n x n grid representing a field of cherries, each cell is one of three possible integers.

0 means the cell is empty, so you can pass through,
1 means the cell contains a cherry that you can pick up and pass through, or
-1 means the cell contains a thorn that blocks your way.
Return the maximum number of cherries you can collect by following the rules below:

Starting at the position (0, 0) and reaching (n - 1, n - 1) by moving right or down through valid path cells (cells with value 0 or 1).
After reaching (n - 1, n - 1), returning to (0, 0) by moving left or up through valid path cells.
When passing through a path cell containing a cherry, you pick it up, and the cell becomes an empty cell 0.
If there is no valid path between (0, 0) and (n - 1, n - 1), then no cherries can be collected.
*/



// *************** TO BE COMPLETED ****************
// ****** THIS SOLUTION IS PARTIALLY CORRECT ******
class Solution {
public:
	int cherryPickup(vector<vector<int>>& m) {
		if (!canReach(m)) return 0;
		int R = m.size(), C = m[0].size(), ans = 0;

		ans += collect(m);
		if (ans == 0) return 0;
		ans += collect(m);
		return ans;
	}

	bool canReach(vector<vector<int>>& m) {
		int R = m.size(), C = m[0].size();
		if (m[0][0]==-1 or m[R-1][C-1]==-1) return false;
		bool dp[51][51] = {};
		dp[0][1] = dp[1][0] = true;
		for (int i=1; i <= R; i++)
			for (int j=1; j <= C; j++)
				dp[i][j] = m[i-1][j-1]!=-1 and (dp[i-1][j] or dp[i][j-1]);
		return dp[R][C];
	}

	int collect(vector<vector<int>>& m) {
		int R = m.size(), C = m[0].size(), ans = 0;
		int dp[51][51] = {};
		dp[0][0] = m[0][0];

		for (int j=1; j < C; j++) {
			dp[0][j] = dp[0][j-1] + m[0][j];
			if (m[0][j-1] == -1 or m[0][j] == -1) dp[0][j] = 0;
		}

		for (int i=1; i < R; i++) {
			dp[i][0] = dp[i-1][0] + m[i][0];
			if (m[i-1][0] == -1 or m[i][0] == -1) dp[i][0] = 0;
		}

		for (int i=1; i < R; i++) {
			for (int j=1; j < C; j++) {
				if (m[i][j]==-1 or (m[i-1][j]==-1 && m[i][j-1]==-1))
					continue;
				int top = dp[i-1][j];
				int left = dp[i][j-1];
				dp[i][j] = max(top, left) + m[i][j];
			}
		}

		// empty the optimal path taken
		m[R-1][C-1] = 0;

		int i=R-1, j=C-1;
		while (i > 0 or j > 0) {
			int top = i>0 ? dp[i-1][j] : -1;
			int left = j>0 ? dp[i][j-1] : -1;
			if (top > left) {
				i--;
				if (m[i][j] != -1) m[i][j] = 0;
			} else {
				j--;
				if (m[i][j] != -1) m[i][j] = 0;
			}
		}
		
		return dp[R-1][C-1];
	}
};