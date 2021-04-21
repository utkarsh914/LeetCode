// https://leetcode.com/problems/guess-number-higher-or-lower-ii/



/*
dp[i][j] is the minimal cost to guess from range(i...j).
When you choose an x where i <= x <= j,
you may find the target number from left i...x-1,
or you may find the target number from the x+1...j,
because you don't know which way should go,
so to guarantee you have enough money to find the target,
you need to prepare the more,
which is max(dp[i][x-1], dp[x+1][j]).
*/
class Solution {
	int dp[201][201];
public:
	int getMoneyAmount(int n) {
		memset(dp, -1, sizeof(dp));
		return collect(1, n);
	}

	int collect(int start, int end) {
		if (start >= end) return 0;
		if (dp[start][end] != -1) return dp[start][end];
		int ans = INT_MAX;
		for (int i = start; i <= end; i++) {
			int cur = i + max(collect(start, i-1), collect(i+1, end));
			ans = min(ans, cur);
		}
		return dp[start][end] = ans;
	}
};





/*
More readable and easy to write bottom up solution:

why make the size (n + 2)*(n + 2)?

The edge cases we need to deal with are:
* For M[1][?], when k = 1, then the induction rule will need M[0][n] which should be ignored. We solve this by marking it as 0(i.e. M[0][?] = 0 or just not set the value which makes it 0 default)
* For M[?][n], when k = n, then the induction rule will need M[n + 1][n] which is indexOutOfBound and should be ignored. We solve this by expanding the 2D DP matrix size to (n + 2) * (n + 2)

How to write the two for loops?

If we draw the matrix, then according to the induction rule:
M[i][j] = k + Math.max(M[i][k - 1], M[k + 1][j]) for k = [i : j].
we notice that M[i][k - 1] is in the left of M[i][j],
and M[k + 1][j] is to the bottom of M[i][j].
So we need to compute these value before calculating M[i][j].
So we write the matrix from left to right, from bottom to top
and since i <= j, so we can just iterate half of matrix by starting j from i.
*/

class Solution {
public:
	int getMoneyAmount(int n) {
		int dp[202][202] = {};

		for (int start = n-1; start > 0; start--) { // from bottom to top
			for (int end = start+1; end <= n; end++) { // from left to right
				dp[start][end] = INT_MAX;
				for (int i = start; i <= end; i++) {
					int temp = i + max(dp[start][i-1], dp[i+1][end]);
					dp[start][end] = min(dp[start][end], temp);
				}
			}
		}

		return dp[1][n];
	}
};





class Solution {
public:
	int getMoneyAmount(int n) {
		int dp[201][201] = {};

		for (int end = 2; end <= n; end++) {
			for (int start = end-1; start > 0; start--) {
				int min_ = INT_MAX;
				for (int i = start+1; i < end; i++) {
					int temp = i + max(dp[start][i-1], dp[i+1][end]);
					min_ = min(min_, temp);
				}
				dp[start][end] = (start == end-1) ? start : min_;
			}
		}

		return dp[1][n];
	}
};