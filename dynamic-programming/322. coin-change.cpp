// https://leetcode.com/problems/coin-change/










// ************ MEMOIZATION ************
class Solution {
public:
	int coinChange(vector<int>& coins, int amount) {
		vector<int> dp(amount+1, -1);
		int ans = change(coins, dp, amount);
		return ans < INT_MAX ? ans : -1;
	}
	
	int change(vector<int>& coins, vector<int>& dp, int amount) {
		if (amount == 0) return 0;
		if (amount < 0) return INT_MAX;
		if (dp[amount] != -1) return dp[amount];

		int ans = INT_MAX;
		for (int c : coins) {
			int cost = change(coins, dp, amount - c);
			if (cost != INT_MAX) ans = min(ans, 1 + cost);
		}

		return dp[amount] = ans;
	}
};




// ------- BOTTOM UP O(N^2) space -------
int coinChange(vector<int>& coins, int amount) {
	int dp[coins.size()+1][amount+1];
	
	for (int i = 0; i <= coins.size(); i++) {
		for (int a = 0; a <= amount; a++) {
			if (i == 0) dp[i][a] = amount + 1; // for no coins, not possible
			else if (a == 0) dp[i][a] = 0; // for zero amount, no coins needed
			else {
				dp[i][a] = dp[i-1][a]; // don't take current coin
				if (coins[i-1] <= a) // take current coin, if possible
					dp[i][a] = min(dp[i][a], 1 + dp[i][a - coins[i-1]]);
			}
		}
	}
	
	int ans = dp[coins.size()][amount];
	return ans < amount+1 ? ans : -1;
}




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
//	   coins on outer loop (faster)
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
