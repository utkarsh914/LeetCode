// https://leetcode.com/problems/minimum-falling-path-sum/

// ******* O(N*N) space *******
class Solution {
public:
	int minFallingPathSum(vector<vector<int>>& m) {
		int n = m.size();
		int dp[n][n];
		// first row of dp
		for (int i=0; i<n; i++)
			dp[0][i] = m[0][i];
		
		for (int i=1; i < n; i++) {
			for (int j=0; j < n; j++) {
				int top = dp[i-1][j];
				int topLeft  = (j > 0) ? dp[i-1][j-1] : INT_MAX;
				int topRight = (j+1<n) ? dp[i-1][j+1] : INT_MAX;
				dp[i][j] = min({ top, topLeft, topRight }) + m[i][j];
			}
		}
		
		return *min_element(dp[n-1], dp[n-1]+n);
	}
};





// ******* O(2*N) space *******
class Solution {
public:
	int minFallingPathSum(vector<vector<int>>& m) {
		int n = m.size();
		int dp[2][n];
		// first row of dp
		for (int i=0; i<n; i++)
			dp[0][i] = m[0][i];
		
		for (int i=1; i < n; i++) {
			for (int j=0; j < n; j++) {
				int top = dp[(i+1) % 2][j];
				int topLeft  = (j > 0) ? dp[(i+1) % 2][j-1] : INT_MAX;
				int topRight = (j+1<n) ? dp[(i+1) % 2][j+1] : INT_MAX;
				dp[i % 2][j] = min({ top, topLeft, topRight }) + m[i][j];
			}
		}
		
		return *min_element(dp[(n-1) % 2], dp[(n-1) % 2]+n);
	}
};