// https://leetcode.com/problems/continuous-subarray-sum/

class Solution {
public:
	bool checkSubarraySum(vector<int>& nums, int k) {
		if (nums.size() < 2) return false;

		// k=0 is handled here
		for (int i=1; i<nums.size(); i++)
			if (nums[i]==0 && nums[i-1]==0)
				return true;

		if (k==0) return false; // k can't be zero after above traversal

		unordered_map<int,int> mp; // map, index
		mp.insert({0, -1});
		int preSum = 0;

		for (int i=0; i<nums.size(); i++) {
			preSum += nums[i];
			int mod = preSum % k;
			if (mp.count(mod)) {
				if (i-mp[mod]>=2)
					return true;
			}
			else {
				mp.insert({mod, i});
			}
		}

		return false;
	}
};