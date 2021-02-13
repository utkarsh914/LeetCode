// https://leetcode.com/problems/longest-increasing-subsequence/

class Solution {
public:
	int lengthOfLIS(vector<int>& nums) {
		vector<int> dp(nums.size(), 1);
		int ans = 1;
		for (int i=1; i<nums.size(); i++) {
			for (int j=0; j<i; j++) {
				if (nums[i] > nums[j])
					dp[i] = max(dp[i], dp[j]+1);
			}
			ans = max(ans, dp[i]);
		}
		return ans;
	}
};


// ********* O(nlogn) **********
// https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
class Solution {
public:
	int lengthOfLIS(vector<int>& nums) {
		vector<int> res;
		for(int i=0; i<nums.size(); i++) {
			auto it = std::lower_bound(res.begin(), res.end(), nums[i]);
			if(it==res.end()) res.push_back(nums[i]);
			else *it = nums[i];
		}
		return res.size();
	}
};