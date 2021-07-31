// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/

/*
You are given an array prices where prices[i] is the price of a given stock on the ith day.

Find the maximum profit you can achieve. You may complete at most two transactions.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

 

Example 1:

Input: prices = [3,3,5,0,0,3,1,4]
Output: 6
Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.
Example 2:

Input: prices = [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are engaging multiple transactions at the same time. You must sell before buying again.
Example 3:

Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
Example 4:

Input: prices = [1]
Output: 0
 

Constraints:

1 <= prices.length <= 105
0 <= prices[i] <= 105
*/









/*
---- O(N) time, O(N) space ------
first we store how much profit can we make by making just one transaction,
both in forward and reverse direction,
then use them to find for at most 2 transactions.
*/
class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int size = prices.size(), ans = 0;
		vector<int> fwd(size, 0), rev(size, 0);

		for (int i=0, min_=INT_MAX; i < size; i++) {
			min_ = min(min_, prices[i]);
			fwd[i] = prices[i] - min_;
			if (i > 0) fwd[i] = max(fwd[i], fwd[i-1]);
		}

		for (int i=size-1, max_=INT_MIN; i >= 0; i--) {
			max_ = max(max_, prices[i]);
			rev[i] = max_ - prices[i];
			if (i+1 < size) rev[i] = max(rev[i], rev[i+1]);
		}

		for (int i=0; i < size; i++) {
			int once = fwd[i];
			int twice = i+1 < size ? rev[i+1] : 0;
			ans = max(ans, once + twice);
		}

		return ans;
	}
};









/*
--------- O(N) time, O(1) space --------

Assume we only have 0 money at first;
4 Variables to maintain some interested 'ceilings' so far:
The maximum of
	- if we've just bought 1st stock
	- if we've just sold 1st stock
	- if we've just bought 2nd stock
	- if we've just sold 2nd stock

NOTE: we are tracking the profit that we gain throughout.

*/
class Solution {
public:
	int maxProfit(vector<int>& p) {
		
		int hold1 = INT_MIN, hold2 = INT_MIN;
		// Assume we only have 0 money at first
		int release1 = 0, release2 = 0;
		
		for (int price : p) {
			// The maximum if we've just sold 1st stock so far.
			release1 = max(release1, hold1 + price);
			// The maximum if we've just bought 1st stock so far.
			hold1 = max(hold1, -price);
			// The maximum if we've just sold 2nd stock so far.
			release2 = max(release2, hold2 + price);
			// The maximum if we've just bought 2nd stock so far.
			hold2 = max(hold2, release1 - price);
		}
		
		return max(release1, release2);
	}
};




// generalized for at most k transactions
// see 188. Best Time to Buy and Sell Stock IV
class Solution {
public:
	int maxProfit(vector<int>& prices, int K = 2) {

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
};