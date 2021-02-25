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



/*
The most straightforward way would be looking at actions taken on the i-th day. How many options do we have? The answer is three: buy, sell, rest. Which one should we take? The answer is: we don't really know, but to find out which one is easy. We can try each option and then choose the one that maximizes our profit, provided there are no other restrictions. However, we do have an extra restriction saying no multiple transactions are allowed at the same time, meaning if we decide to buy on the i-th day, there should be 0 stock held in our hand before we buy; if we decide to sell on the i-th day, there should be exactly 1 stock held in our hand before we sell. The number of stocks held in our hand is the hidden factor mentioned above that will affect the action on the i-th day and thus affect the maximum profit.

Therefore our definition of T[i][k] should really be split into two: T[i][k][0] and T[i][k][1], where the former denotes the maximum profit at the end of the i-th day with at most k transactions and with 0 stock in our hand AFTER taking the action, while the latter denotes the maximum profit at the end of the i-th day with at most k transactions and with 1 stock in our hand AFTER taking the action. Now the base cases and the recurrence relations can be written as:

Base cases:
T[-1][k][0] = 0, T[-1][k][1] = -Infinity
T[i][0][0] = 0, T[i][0][1] = -Infinity

Recurrence relations:
T[i][k][0] = max(T[i-1][k][0], T[i-1][k][1] + prices[i])
T[i][k][1] = max(T[i-1][k][1], T[i-1][k-1][0] - prices[i])

For the base cases, T[-1][k][0] = T[i][0][0] = 0 has the same meaning as before while T[-1][k][1] = T[i][0][1] = -Infinity emphasizes the fact that it is impossible for us to have 1 stock in hand if there is no stock available or no transactions are allowed.

For T[i][k][0] in the recurrence relations, the actions taken on the i-th day can only be rest and sell, since we have 0 stock in our hand at the end of the day. T[i-1][k][0] is the maximum profit if action rest is taken, while T[i-1][k][1] + prices[i] is the maximum profit if action sell is taken. Note that the maximum number of allowable transactions remains the same, due to the fact that a transaction consists of two actions coming as a pair -- buy and sell. Only action buy will change the maximum number of transactions allowed (well, there is actually an alternative interpretation, see my comment below).

For T[i][k][1] in the recurrence relations, the actions taken on the i-th day can only be rest and buy, since we have 1 stock in our hand at the end of the day. T[i-1][k][1] is the maximum profit if action rest is taken, while T[i-1][k-1][0] - prices[i] is the maximum profit if action buy is taken. Note that the maximum number of allowable transactions decreases by one, since buying on the i-th day will use one transaction, as explained above.

To find the maximum profit at the end of the last day, we can simply loop through the prices array and update T[i][k][0] and T[i][k][1] according to the recurrence relations above. The final answer will be T[i][k][0] (we always have larger profit if we end up with 0 stock in hand).
*/
class Solution {
public:
	int maxProfit(int K, vector<int>& prices) {
		int size = prices.size();
		if (K >= size/2) return quickSolve(prices);

		int dp[size+1][K+1][2];

		for (int i=0; i <= size; i++) {
			for (int k=0; k <= K; k++) {
				if (i == 0) {
					dp[i][k][0] = 0;
					dp[i][k][1] = INT_MIN;
				}
				else if (k == 0) {
					dp[i][k][0] = 0;
					dp[i][k][1] = INT_MIN;
				}
				else {
					dp[i][k][0] = max( dp[i-1][k][0], dp[i-1][k][1] + prices[i-1] );
					dp[i][k][1] = max( dp[i-1][k][1], dp[i-1][k-1][0] - prices[i-1] );
				}
			}
		}

		return dp[size][K][0];
	}

	int quickSolve(vector<int>& prices, int result = 0) {
		for (auto i = 1; i < prices.size(); ++i)
			result += max(0, prices[i] - prices[i - 1]);
		return result;
	}
};





// ********** O(K) space **********
class Solution {
public:
	int maxProfit(int K, vector<int>& prices) {
		int size = prices.size();
		if (K >= size/2) return quickSolve(prices);

		int dp[2][K+1][2];

		for (int i=0; i <= size; i++) {
			for (int k=0; k <= K; k++) {
				if (i == 0 or k == 0) {
					dp[i%2][k][0] = 0;
					dp[i%2][k][1] = INT_MIN;
				}
				else {
					dp[i%2][k][0] = max( dp[(i+1)%2][k][0], dp[(i+1)%2][k][1] + prices[i-1] );
					dp[i%2][k][1] = max( dp[(i+1)%2][k][1], dp[(i+1)%2][k-1][0] - prices[i-1] );
				}
			}
		}

		return dp[size%2][K][0];
	}

	int quickSolve(vector<int>& prices, int result = 0) {
		for (auto i = 1; i < prices.size(); ++i)
			result += max(0, prices[i] - prices[i - 1]);
		return result;
	}
};





// ********** O(K) space **********
class Solution {
public:
	int maxProfit(int K, vector<int>& prices) {
		int size = prices.size();
		if (K >= size/2) return quickSolve(prices);

		vector<int> dp_ik0(K+1, 0);
		vector<int> dp_ik1(K+1, INT_MIN);

		for (int price : prices) {
			for (int k=K; k >= 0; k--) {
				dp_ik0[k] = max( dp_ik0[k], dp_ik1[k] + price );
				dp_ik1[k] = max( dp_ik1[k], dp_ik0[k-1] - price );
			}
		}

		return dp_ik0[K];
	}

	int quickSolve(vector<int>& prices, int result = 0) {
		for (auto i = 1; i < prices.size(); ++i)
			result += max(0, prices[i] - prices[i - 1]);
		return result;
	}
};