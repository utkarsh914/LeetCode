// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/

class Solution {
	int dp[1001][101];
public:
	int maxProfit(int k, vector<int>& prices) {
		memset(dp, -1, sizeof(dp));
		return buy(prices, 0, k);
	}

	int buy(vector<int>& prices, int start, int k) {
		if (start == prices.size() or k == 0) return 0;
		if (dp[start][k] != -1) return dp[start][k];
		int ans = 0, min_ = INT_MAX;
		for (int i = start; i < prices.size(); i++) {
			min_ = min(min_, prices[i]);
			int curProfit = prices[i] - min_;
			int nextProfit = buy(prices, i+1, k-1);
			ans = max( ans, curProfit + nextProfit);
		}
		return dp[start][k] = ans;
	}
};