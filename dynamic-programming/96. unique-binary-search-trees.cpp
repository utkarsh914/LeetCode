// https://leetcode.com/problems/unique-binary-search-trees/

// similar to: 894. all-possible-full-binary-trees

class Solution {
public:
	int numTrees(int n) {
	
		vector<vector<int>> dp(n+2, vector<int>(n+2, 0) );

		for (int i=1; i<=n+1; i++)
			dp[i][i-1] = 1;

		for (int len=1; len<=n; len++) {
			for (int start=1, end=start+len-1; end<=n; start++,end++) {
				if (len == 1) {
					dp[start][end] = 1;
					continue;
				}
				for (int pivot=start; pivot<=end; pivot++) {
					int left = dp[start][pivot-1];
					int right = dp[pivot+1][end];
					dp[start][end] += left*right;
				}
			}
		}

		return dp[1][n];
	}
};