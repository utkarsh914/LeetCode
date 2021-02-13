
class Solution {
public:
	// basic idea is similar to 'maximal square problem'
	// count the size of maximum length square with M[i][j] as its bottom right corner
	// then sum these values of whole dp to get total squares
	int countSquares(vector<vector<int>>& M) {
		if (!M.size()) return 0;
		int R=M.size(), C=M[0].size();
		int dp[R][C];
		int ans=0;
		for (int i=0; i<R; i++) {
			for (int j=0; j<C; j++) {
				if (i==0 or j==0) dp[i][j]=M[i][j];
				else if (M[i][j]==0) dp[i][j]=0;
				else dp[i][j] = min(dp[i-1][j-1], min(dp[i][j-1],dp[i-1][j])) + 1;
				ans += dp[i][j];
			}
		}
		return ans;
	}
};