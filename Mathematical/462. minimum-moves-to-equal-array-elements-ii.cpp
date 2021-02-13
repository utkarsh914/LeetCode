// https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/

class Solution {
public:
	int minMoves2(vector<int>& nums) {
		int count = 0, size = nums.size();
		auto itr = nums.begin() + size/2;
		nth_element(nums.begin(), itr, nums.end());
		int median = *itr;
		for (int n:nums)
			count += abs(n - median);
		return count;
	}
};