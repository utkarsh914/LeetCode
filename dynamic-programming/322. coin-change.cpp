// https://leetcode.com/problems/coin-change/

// ********* BOTTOM-UP DP ********
// amount on outer loop
class Solution {
public:
	int coinChange(vector<int>& coins, int amount) {
		vector<int> dp(amount+1, INT_MAX);
		dp[0] = 0;
		for (int a=1; a<=amount; a++) {
			for (int c: coins) {
				if (c<=a && dp[a-c]!=INT_MAX)
					dp[a] = min(dp[a], 1+dp[a-c]);
			}
		}
		return (dp[amount]==INT_MAX) ? -1 : dp[amount];
	}
};


// ********* BOTTOM-UP DP ********
//       coins on outer loop (faster)
class Solution {
public:
	int coinChange(vector<int>& coins, int amount) {
		vector<int> dp(amount+1, amount+1);
		dp[0] = 0;
		for (int c: coins) {
			for (int a=c; a<=amount; a++) { // note that a=c
				dp[a] = min(dp[a], 1+dp[a-c]);
			}
		}
		return (dp[amount]==amount+1) ? -1 : dp[amount];
	}
};





// ************ MEMORIZATION ************
class Solution {
	int change(vector<int>& coins, vector<int>& dp, int amount) {
		if (amount==0) return 0;
		if (amount < 0) return -1;
		if (dp[amount] != -1) return dp[amount];
		int ans = INT_MAX;
		for (int c:coins) {
			int cost = change(coins, dp, amount-c);
			if (cost!=-1 && 1+cost<ans) ans=1+cost;
		}
		return dp[amount] = ans==INT_MAX ? -1 : ans;
	}
public:
	int coinChange(vector<int>& coins, int amount) {
		vector<int> dp(amount+1, -1);
		return change(coins, dp, amount);
	}
};