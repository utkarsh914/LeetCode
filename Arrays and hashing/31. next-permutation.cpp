// https://leetcode.com/problems/next-permutation/

class Solution {
public:
	void nextPermutation(vector<int>& nums) {
		int i=nums.size()-2;
		// from last, first i where i,i+1 don't fllow decreasing order
		while (i>=0 && nums[i]>=nums[i+1]) i--;
		// already largest
		if (i < 0) {
			reverse(nums.begin()+i+1, nums.end());
			return;
		}
		// from last, find first elem just greater than nums[i]
		int j = nums.size()-1;
		while (j>=0 && nums[j]<=nums[i]) j--;
		swap(nums[i], nums[j]);
		reverse(nums.begin()+i+1, nums.end());
	}
};