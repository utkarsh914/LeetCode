// https://leetcode.com/problems/maximum-length-of-pair-chain/

class Solution {
	static bool comp(vector<int>& p1, vector<int>& p2) {
		return p1[1]<p2[1];
	}
	int dp[1001];
	int find(vector<vector<int>>& pairs, vector<int>& prev, int start) {
		if (start >= pairs.size()) return 0;
		if (dp[start] != -1) return dp[start];
		int take=0, notTake=0;
		if (pairs[start][0] > prev[1])
			take = 1 + find(pairs, pairs[start], start+1);
		notTake = find(pairs, prev, start+1);
		return dp[start] = max(take, notTake);
	}
public:
	int findLongestChain(vector<vector<int>>& pairs) {
		memset(dp, -1, sizeof(dp));
		sort(pairs.begin(), pairs.end(), comp);
		vector<int> prev = {INT_MIN, INT_MIN};
		return find(pairs, prev, 0);
		// for (auto& p:pairs)	cout<<"("<<p[0]<<","<<p[1]<<") ";
	}
};