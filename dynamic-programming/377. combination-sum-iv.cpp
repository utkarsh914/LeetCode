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


// *********** DP MEMORIZATION ********
class Solution {
public:

	vector<int> dp;

	int combinationSum4(vector<int>& arr, int target) {
		dp = vector<int> (target+1, -1);
		return recur(arr, target);
	}

	int recur(vector<int>& arr, int target) {
		if (target == 0) return 1;
		if (dp[target] != -1) return dp[target];
		int ans = 0;
		for (auto i:arr) {
			if (i<=target) ans += recur(arr, target-i);
		}
		return dp[target]=ans;
	}

};