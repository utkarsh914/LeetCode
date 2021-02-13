// https://leetcode.com/problems/constrained-subsequence-sum/

/*
Given an integer array nums and an integer k, return the maximum sum of a non-empty subsequence of that array
such that for every two consecutive integers in the subsequence, nums[i] and nums[j], where i < j,
the condition j - i <= k is satisfied.
A subsequence of an array is obtained by deleting some number of elements (can be zero) from the array,
leaving the remaining elements in their original order.

Example 1:

Input: nums = [10,2,-10,5,20], k = 2
Output: 37
Explanation: The subsequence is [10, 2, 5, 20].
Example 2:

Input: nums = [-1,-2,-3], k = 1
Output: -1
Explanation: The subsequence must be non-empty, so we choose the largest number.
*/

// similar to: 1696. Jump game VI, and 239. Sliding window maximum

class Solution {
public:
	int constrainedSubsetSum(vector<int>& n, int k) {
		deque<array<int,2>> dq; // {value, index}
		int ans = INT_MIN;
		
		for (int i=n.size()-1; i>=0; i--) {
			// remove out of range/negative ele from front
			// removing negatives bcz previously calculated -ve sums will only decrease the curr sum
			// and we won't collect the max possible sum
			while (!dq.empty() && (dq.front()[1] > i+k or dq.front()[0] <= 0))
				dq.pop_front();

			int curScore = n[i];
			if (!dq.empty()) curScore += dq.front()[0];

			// push curScore to dq keeping it monotonous decreasing
			while (!dq.empty() && curScore > dq.back()[0])
				dq.pop_back();
			dq.push_back({ curScore, i });
			// update maximum ans
			ans = max(ans, curScore);
		}
		
		return ans;
	}
};