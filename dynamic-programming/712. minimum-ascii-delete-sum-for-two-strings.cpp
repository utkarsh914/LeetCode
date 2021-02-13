// https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/

class Solution {
public:
	int minimumDeleteSum(string& s1, string& s2) {
		int size1 = s1.size(), size2 = s2.size();
		int dp[size1+1][size2+1];

		for (int i=size1; i >= 0; i--) {
			for (int j=size2; j >= 0; j--) {
				if (i == size1 && j == size2) dp[i][j] = 0;
				else if (i == size1) dp[i][j] = s2[j] + dp[i][j+1];
				else if (j == size2) dp[i][j] = s1[i] + dp[i+1][j];
				else {
					if (s1[i] == s2[j]) dp[i][j] = dp[i+1][j+1];
					else dp[i][j] = min( s1[i] + dp[i+1][j], s2[j] + dp[i][j+1] );
				}
			}
		}

		return dp[0][0];
	}
};