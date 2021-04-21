/*
https://leetcode.com/problems/combination-sum-iv/

Given an integer array with all positive numbers and no duplicates,
find the number of possible combinations that add up to a positive integer target.

Example:
nums = [1, 2, 3]
target = 4

The possible combination ways are:
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)
Note that different sequences are counted as different combinations.
Therefore the output is 7.
*/


// *********** DP MEMOIZATION ********
class Solution {
	vector<int> dp;
public:
	int combinationSum4(vector<int>& arr, int target) {
		dp.resize(target+1, -1);
		return recur(arr, target);
	}

	int recur(vector<int>& arr, int target) {
		if (target == 0) return 1;
		if (dp[target] != -1) return dp[target];
		int ans = 0;
		for (auto i : arr) {
			if (i <= target)
				ans += recur(arr, target - i);
		}
		return dp[target] = ans;
	}

};





class Solution {
public:
	int combinationSum4(vector<int>& coins, int target) {
		vector<unsigned long> dp(target + 1, 0);
		dp[0] = 1; // to make 0, there is only 1 way(to not take any coin)

		for (int sum = 1; sum <= target; sum++) {
			for (int coin : coins) {
				if (coin <= sum)
					dp[sum] += dp[sum - coin];
			}
		}

		return dp[target];
	}
};





/*
If you accidentally remember the code in Coin Change 2,
you may find the solution to this problem is basically the same with that,
except the order of for loop.
*/

// Coin Change 2
int change(int amount, vector<int>& coins) {
	vector<int> dp(amount+1, 0);
	dp[0] = 1; // to make 0, there is only 1 way(to not take any coin)
	
	for (int coin : coins)
		for (int a = coin; a <= amount; a++)
			dp[a] += dp[a - coin];

	return dp[amount];
}


// this problem
int combinationSum4(vector<int>& coins, int target) {
	vector<unsigned long> dp(target + 1, 0);
	dp[0] = 1; // to make 0, there is only 1 way(to not take any coin)

	for (int sum = 1; sum <= target; sum++) {
		for (int coin : coins) {
			if (coin <= sum)
				dp[sum] += dp[sum - coin];
		}
	}

	return dp[target];
}
/*
In this problem, we are required to count the duplicate results.
However, in coin change, 1 + 1 + 2 is the same with 1 + 2 + 1.
The order of the for loop actually makes these two different problems.

coin change 2 is combination sum
and this problem is in fact permutation sum since order matters.
*/