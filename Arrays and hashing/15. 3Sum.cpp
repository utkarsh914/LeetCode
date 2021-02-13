/*
https://leetcode.com/problems/3sum/
*/

class Solution {
public:
	vector<vector<int>> threeSum(vector<int>& nums);
};

vector<vector<int>> Solution::threeSum(vector<int>& nums) {

	vector<vector<int>> ans;
	sort(nums.begin(), nums.end());
	if (nums.size()<3) return ans;

	for (int i=0; i<nums.size()-2; i++) {
		if (i>0 and nums[i]==nums[i-1])
			continue;
		if (nums[i]>0)
			break;

		int target = -nums[i];
		int lo = i+1;
		int hi = nums.size()-1;
		while (lo < hi) {
			int sum = nums[lo] + nums[hi];
			if (sum == target) {
				ans.push_back({nums[i], nums[lo], nums[hi]});
				while (lo<hi and nums[lo]==nums[lo+1]) lo++;
				while (lo<hi and nums[hi]==nums[hi-1]) hi--;
				lo++, hi--;
			}
			else if (sum < target)
				lo++;
			else
				hi--;
		}
	}
	
	return ans;
}

static auto _______ = [](){
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	return 0;
}();
