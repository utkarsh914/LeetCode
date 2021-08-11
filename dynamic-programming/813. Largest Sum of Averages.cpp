// https://leetcode.com/problems/largest-sum-of-averages/

/*
You are given an integer array nums and an integer k. You can partition the array into at most k non-empty adjacent subarrays. The score of a partition is the sum of the averages of each subarray.

Note that the partition must use every integer in nums, and that the score is not necessarily an integer.

Return the maximum score you can achieve of all the possible partitions. Answers within 10-6 of the actual answer will be accepted.

 

Example 1:

Input: nums = [9,1,2,3,9], k = 3
Output: 20.00000
Explanation: 
The best choice is to partition nums into [9], [1, 2, 3], [9]. The answer is 9 + (1 + 2 + 3) / 3 + 9 = 20.
We could have also partitioned nums into [9, 1], [2], [3, 9], for example.
That partition would lead to a score of 5 + 2 + 6 = 13, which is worse.
Example 2:

Input: nums = [1,2,3,4,5,6,7], k = 4
Output: 20.50000
 

Constraints:

1 <= nums.length <= 100
1 <= nums[i] <= 104
1 <= k <= nums.length
*/






/*
similar to https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule/

Time - O(k * N * N)
*/
class Solution {
	double dp[101][101] = {};
public:
	double largestSumOfAverages(vector<int>& nums, int k) {
		return partition(nums, 0, k);
	}
	
	double partition(vector<int>& nums, int start, int k) {
		if (start == nums.size()) return 0;
		if (k <= 0) return INT_MIN;
		if (dp[start][k] > 0) return dp[start][k];
		
		double sum = 0, n = 0, ans = 0;
		for (int i = start; i < nums.size(); i++) {
			sum += nums[i], n++;
			ans = max(ans, sum/n + partition(nums, i+1, k-1));
		}
		
		return dp[start][k] = ans;
	}
};