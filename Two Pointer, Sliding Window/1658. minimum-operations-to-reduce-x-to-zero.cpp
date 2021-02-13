// https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/

/*
	instead of finding the minimum prefix + suffix, find the maximum subarray.
*/

class Solution {
	int maxSubArrayLen(int k, vector<int>& nums) {
		int maxL = INT_MIN;
		int sum=0, i=0, j=0;
		while (j < nums.size()) {
			sum += nums[j++];
			while (sum > k && i<j)
				sum -= nums[i++];
			if (sum == k) maxL = max(maxL, j-i);
		}
		return maxL==INT_MIN ? -1 : maxL;
	}
public:
	int minOperations(vector<int>& n, int x) {
		if (x==0) return 0;
		int sum = accumulate(n.begin(), n.end(), 0);
		int k = sum-x;
		if (k<0) return -1;
		int maxL = maxSubArrayLen(k, n);
		return maxL==-1 ? -1 : n.size()-maxL;
	}
};