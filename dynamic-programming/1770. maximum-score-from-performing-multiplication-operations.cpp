// https://leetcode.com/problems/maximum-score-from-performing-multiplication-operations/

/*
You are given two integer arrays nums and multipliers of size n and m respectively, where n >= m. The arrays are 1-indexed.

You begin with a score of 0. You want to perform exactly m operations. On the ith operation (1-indexed), you will:

Choose one integer x from either the start or the end of the array nums.
Add multipliers[i] * x to your score.
Remove x from the array nums.
Return the maximum score after performing m operations.

 

Example 1:

Input: nums = [1,2,3], multipliers = [3,2,1]
Output: 14
Explanation: An optimal solution is as follows:
- Choose from the end, [1,2,3], adding 3 * 3 = 9 to the score.
- Choose from the end, [1,2], adding 2 * 2 = 4 to the score.
- Choose from the end, [1], adding 1 * 1 = 1 to the score.
The total score is 9 + 4 + 1 = 14.


Constraints:

n == nums.length
m == multipliers.length
1 <= m <= 103
m <= n <= 105
-1000 <= nums[i], multipliers[i] <= 1000

*/

class Solution {
	int dp[1001][1001];
	bool vis[1001][1001];
public:
	int maximumScore(vector<int>& nums, vector<int>& multipliers) {
		memset(dp, -1, sizeof(dp));
		memset(vis, 0, sizeof(vis));
		return cal(nums, multipliers, 0, 0, 0);
	}

	int cal(vector<int>& n, vector<int>& mul, int left, int right, int ind) {
		if (ind == mul.size()) return 0;
		if (vis[left][right]) return dp[left][right];
		int start = left, end = n.size()-1-right;
		int takeStart = (mul[ind] * n[start]) + cal(n, mul, left+1, right, ind+1);
		int takeEnd   = (mul[ind] * n[end])   + cal(n, mul, left, right+1, ind+1);
		vis[left][right] = true;
		return dp[left][right] = max(takeStart, takeEnd);
	}
};