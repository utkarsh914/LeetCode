/*
https://leetcode.com/problems/unique-paths-ii/

A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and space is marked as 1 and 0 respectively in the grid.
*/

public int uniquePathsWithObstacles(int[][] obstacleGrid) {
	int width = obstacleGrid[0].length;
	int[] dp = new int[width];
	dp[0] = 1;
	for (int[] row : obstacleGrid) {
		for (int j = 0; j < width; j++) {
			if (row[j] == 1)
				dp[j] = 0;
			else if (j > 0)
				dp[j] += dp[j - 1];
		}
	}
	return dp[width - 1];
}

/*
More explanation:
This is a typical 2D DP problem, we can store value in 2D DP array,
but since we only need to use value at dp[i - 1][j] and dp[i][j - 1]
to update dp[i][j], we don't need to store the whole 2D table,
but instead store value in an 1D array, and update data
by using dp[j] = dp[j] + dp[j - 1], (where here dp[j] corresponding to
the dp[i - 1][j]) and dp[j - 1] corresponding to the dp[i][j - 1] in the 2D array)

dp[j] += dp[j - 1];
is
dp[j] = dp[j] + dp[j - 1];
which is new dp[j] = old dp[j] + dp[j-1]
which is current cell = top cell + left cell
*/