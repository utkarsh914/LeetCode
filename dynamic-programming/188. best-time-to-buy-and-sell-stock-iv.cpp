// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/

/*
You are given an integer array prices where prices[i]
is the price of a given stock on the ith day, and an integer k.

Find the maximum profit you can achieve.
You may complete at most k transactions.

Note: You may not engage in multiple transactions simultaneously
(i.e., you must sell the stock before you buy again).

 

Example 1:

Input: k = 2, prices = [2,4,1]
Output: 2
Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4),
profit = 4-2 = 2.

Example 2:

Input: k = 2, prices = [3,2,6,5,0,3]
Output: 7
Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6),
profit = 6-2 = 4. Then buy on day 5 (price = 0) and sell on day 6 (price = 3),
profit = 3-0 = 3.
 

Constraints:

0 <= k <= 100
0 <= prices.length <= 1000
0 <= prices[i] <= 1000
*/





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
				if (i == 0 or k == 0) {
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



// -------- more concise --------
int maxProfit(int K, vector<int>& prices) {
	int N = prices.size();
	int hold[N+1][K+1], sell[N+1][K+1];

	for (int l = 0; l <= N; l++) {
		for (int k = 0; k <= K; k++) {
			if (l == 0 or k == 0) {
				sell[l][k] = 0;
				hold[l][k] = INT_MIN;
			}
			else {
				sell[l][k] = max(sell[l-1][k], hold[l-1][k] + prices[l-1]);
				hold[l][k] = max(hold[l-1][k], sell[l-1][k-1] - prices[l-1]);
			}
		}
	}

	return sell[N][K];
}




// ********** O(K) space **********
int maxProfit(int K, vector<int>& prices) {
	int size = prices.size();

	int dp[2][K+1][2];

	for (int i=0; i <= size; i++) {
		int cur = i % 2, prev = !cur;
		for (int k=0; k <= K; k++) {
			if (i == 0 or k == 0) {
				dp[cur][k][0] = 0;
				dp[cur][k][1] = INT_MIN;
			}
			else {
				dp[cur][k][0] = max( dp[prev][k][0], dp[prev][k][1] + prices[i-1] );
				dp[cur][k][1] = max( dp[prev][k][1], dp[prev][k-1][0] - prices[i-1] );
			}
		}
	}

	return dp[size % 2][K][0];
}





// ********** O(K) space **********
class Solution {
public:
	int maxProfit(int K, vector<int>& prices) {
		int size = prices.size();

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
};