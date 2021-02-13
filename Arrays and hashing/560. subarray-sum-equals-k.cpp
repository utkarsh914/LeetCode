// https://leetcode.com/problems/subarray-sum-equals-k/

// ******** using prefix sum ******
class Solution {
public:
	int subarraySum(vector<int>& nums, int k) {
		unordered_map<int,int> mp; // pair<presum, freq>
		mp.insert({0, 1});
		int count = 0, preSum = 0;
		for (int i=0; i<nums.size(); i++) {
			preSum += nums[i];
			if (mp.count(preSum - k))
				count += mp[preSum-k];
			mp[preSum]++;
		}
		return count;
	}
};