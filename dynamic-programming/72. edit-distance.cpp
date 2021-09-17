// https://leetcode.com/problems/edit-distance/



// ******** BOTTOM UP DP ********
class Solution {
public:
	int minDistance(string& w1, string& w2) {
		int dp[501][501];
		int size1 = w1.size(), size2 = w2.size();

		for (int i = size1; i >= 0; i--) {
			for (int j = size2; j >= 0; j--) {
				if (i == size1 and j==size2) dp[i][j] = 0;
				else if (i == size1) dp[i][j] = size2 - j;
				else if (j == size2) dp[i][j] = size1 - i;
				else if (w1[i] == w2[j]) dp[i][j] = dp[i+1][j+1];
				else {
					int insert  = 1 + dp[i][j+1];
					int delette = 1 + dp[i+1][j];
					int replace = 1 + dp[i+1][j+1];
					dp[i][j] = min({ insert, delette, replace });
				}
			}
		}

		return dp[0][0];
	}
};





// ******** TOP-DOWN (MEMORIZATION) ********
class Solution {
	int dp[500][500];
public:
	int minDistance(string& w1, string& w2) {
		memset(dp, -1, sizeof(dp));
		return edit(w1, w2, 0, 0);
	}

	int edit(string& w1, string& w2, int s1, int s2) {

		if (s1 == w1.size() and s2 == w2.size()) return 0;
		if (s1 == w1.size()) return w2.size() - s2;
		if (s2 == w2.size()) return w1.size() - s1;
		// return cached result
		if (dp[s1][s2] != -1) return dp[s1][s2];
		
		if (w1[s1] == w2[s2])
			return edit(w1, w2, s1+1, s2+1);
		
		int insert  = 1 + edit(w1, w2, s1, s2+1);
		int del     = 1 + edit(w1, w2, s1+1, s2);
		int replace = 1 + edit(w1, w2, s1+1, s2+1);

		return dp[s1][s2] = min({ insert, del, replace });
	}
};