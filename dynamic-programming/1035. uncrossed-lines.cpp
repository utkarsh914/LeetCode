// https://leetcode.com/problems/uncrossed-lines/


// basically we just need to find LCS
// but this approach is a bit different

class Solution {
	int dp[501][501];
	unordered_map<int, vector<int>> map;
public:
	int maxUncrossedLines(vector<int>& A, vector<int>& B) {
		memset(dp, -1, sizeof(dp));
		for (int i=0; i<B.size(); i++)
			map[B[i]].push_back(i);
		return cross(A, B, 0, 0);
	}

	int cross(vector<int>& A, vector<int>& B, int sa, int sb) {
		if (sa == A.size() or sb == B.size()) return 0;
		if (dp[sa][sb] != -1)	return dp[sa][sb];

		int ans = 0;
		for (int i=sa; i<A.size(); i++) {
			vector<int>& indices = map[A[i]];
			for (int j:indices) {
				if (j >= sb)
					ans = max(ans, 1 + cross(A,B,i+1,j+1));
			}
		}

		return dp[sa][sb] = ans;
	}
};