// https://leetcode.com/problems/minimum-size-subarray-sum/

/*
Given an array of positive integers nums and a positive integer target,
return the minimal length of a contiguous subarray [numsl, numsl+1, ..., numsr-1, numsr]
of which the sum is greater than or equal to target. If there is no such subarray, return 0 instead.

Example 1:

Input: target = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: The subarray [4,3] has the minimal length under the problem constraint.
*/

// https://leetcode.com/problems/minimum-size-subarray-sum/

// ******** two pointer ********
class Solution {
public:
	int minSubArrayLen(int k, vector<int>& nums) {
		int minL = INT_MAX;
		int sum=0, i=0, j=0;
		while (j < nums.size()) {
			sum += nums[j++];
			while (sum >= k) {
				minL = min(minL, j-i);
				sum -= nums[i++];
			}
		}
		return minL==INT_MAX ? 0 : minL;
	}
};