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