// https://leetcode.com/problems/partition-array-for-maximum-sum/

/*
Given an integer array arr, you should partition the array into (contiguous) subarrays of length at most k.
After partitioning, each subarray has their values changed to become the maximum value of that subarray.
Return the largest sum of the given array after partitioning.

Example 1:

Input: arr = [1,15,7,9,2,5,10], k = 3
Output: 84
Explanation: arr becomes [15,15,15,9,10,10,10]
Example 2:

Input: arr = [1,4,1,5,7,3,6,1,9,9,3], k = 4
Output: 83
*/

class Solution {
public:
	int maxSumAfterPartitioning(vector<int>& arr, int k) {
		int size = arr.size();
		vector<int> dp(size, 0);

		int curmax = INT_MIN;
		for (int i=size-1; i>=size-k; i--) {
			curmax = max(curmax, arr[i]);
			dp[i] = (size-i)*curmax;
		}

		for (int i=size-k-1; i>=0; i--) {
			int tempAns = curmax = INT_MIN;
			for (int j=i, len=1; j<i+k; j++,len++) {
				curmax = max(curmax, arr[j]);
				tempAns = max(tempAns, curmax*len + dp[j+1]);
			}
			dp[i] = tempAns;
		}

		return dp[0];
	}
};