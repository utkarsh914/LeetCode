// https://leetcode.com/problems/product-of-array-except-self/

/*
compute cumulative product from left in ans array
keep computing cumulative product from right in nums array,
and determining the ans simultaneously
*/
class Solution {
public:
	vector<int> productExceptSelf(vector<int>& nums) {
		vector<int> ans(nums.size(), nums[0]);
		// store left product in o/p array
		for (int i=1; i < nums.size(); i++) {
			ans[i] = nums[i] * ans[i-1];
		}
		// store right product in nums array, and simultaneously
		// fill the answer array
		for (int i=nums.size()-1; i >= 0; i--) {
			int left = i>0 ? ans[i-1] : 1;
			int right = i+1<nums.size() ? nums[i+1] : 1;
			ans[i] = left * right;
			nums[i] = nums[i] * right;
		}

		return ans;
	}
};