// https://leetcode.com/problems/find-all-duplicates-in-an-array/

class Solution {
public:
	vector<int> findDuplicates(vector<int>& nums) {
		vector<int> ans;
		for (int n:nums) {
			if (nums[abs(n)-1] < 0) ans.push_back(abs(n));
			else nums[abs(n)-1] *= -1;
		}
		return ans;
	}
};