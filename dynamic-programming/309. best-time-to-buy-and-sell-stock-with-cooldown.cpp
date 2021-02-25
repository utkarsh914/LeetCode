// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/

/*
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times) with the following restrictions:

You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1 day)
Example:

Input: [1,2,3,0,2]
Output: 3 
Explanation: transactions = [buy, sell, cooldown, buy, sell]
*/

class Solution {
	vector<int> dp;
public:
	int maxProfit(vector<int>& prices) {
		dp.resize(prices.size(), -1);
		return buy(prices, 0);
	}

	int buy(vector<int>& prices, int start) {
		if (start >= prices.size()) return 0;
		if (dp[start] != -1) return dp[start];
		int ans = 0;
		for (int i=start, min_=INT_MAX; i < prices.size(); i++) {
			min_ = min(min_, prices[i]);
			int curProfit = prices[i] - min_;
			int nextProfit = buy(prices, i+2);
			ans = max(ans, curProfit + nextProfit);
		}
		return dp[start] = ans;
	}
	
};