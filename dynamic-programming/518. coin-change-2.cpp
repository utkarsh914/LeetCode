// https://leetcode.com/problems/coin-change-2/

/*
You are given coins of different denominations and a total amount of money.
Write a function to compute the number of combinations that make up that amount.
You may assume that you have infinite number of each kind of coin.

Example 1:

Input: amount = 5, coins = [1, 2, 5]
Output: 4
Explanation: there are four ways to make up the amount:
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1
*/



class Solution {
public:
	int change(int amount, vector<int>& coins) {
		int dp[coins.size()+1][amount+1];
		// 0 ways possible if now coins available
		for (int i = 1; i <= amount; i++)
			dp[0][i] = 0;
		// to make 0, there is only 1 way(to not take any coin)
		for (int i = 0; i <= coins.size(); i++)
			dp[i][0] = 1;

		for (int i = 1; i <= coins.size(); i++) {
			for (int j = 1; j <= amount; j++) {
				int notTake = dp[i-1][j];
				int take = (j >= coins[i-1]) ? dp[i][j - coins[i-1]] : 0;
				dp[i][j] = take + notTake;
			}
		}

		return dp[coins.size()][amount];
	}
};





// ******* using 1-D DP *******
/*
as we are updating values from left to right,
and we need the prev value (updated in the current loop only) from curr row.
And we need the value from prev row for current column.

we can use a 1D dp here. As the values from the prev row
are already present when we need them.
And for the values from cur row, which were updated in the current loop,
are obvously present and updated.
*/
class Solution {
public:
	int change(int amount, vector<int>& coins) {
		vector<int> dp(amount+1, 0);
		dp[0] = 1; // to make 0, there is only 1 way(to not take any coin)
		
		for (int coin : coins)
			for (int a = coin; a <= amount; a++)
				dp[a] += dp[a - coin];

		return dp[amount];
	}
};