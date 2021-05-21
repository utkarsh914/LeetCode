// https://leetcode.com/problems/random-pick-index/

class Solution {
	unordered_map<int, vector<int>> map;
public:
	Solution(vector<int>& nums) {
		for (int i = 0; i < nums.size(); i++) {
			map[nums[i]].push_back(i);
		}
	}
	
	int pick(int target) {
		long lower = 0, upper = map[target].size()-1;
		long r = (rand() % (upper - lower + 1)) + lower;
		return map[target][r];
	}
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * int param_1 = obj->pick(target);
 */