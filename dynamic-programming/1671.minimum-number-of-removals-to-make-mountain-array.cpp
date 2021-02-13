// https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/

class Solution {
	// takes O(nlogn)
	vector<int> LIS_using_BS(vector<int>& nums) {
		vector<int> dp(nums.size(), 1);
		vector<int> res;
		for(int i=0; i<nums.size(); i++) {
			auto it = std::lower_bound(res.begin(), res.end(), nums[i]);
			if(it==res.end()) res.push_back(nums[i]);
			else *it = nums[i];
			dp[i] = res.size();
		}
		return dp;
	}
	// O(n^2)
	vector<int> LIS(vector<int>& nums) {
		vector<int> dp(nums.size(), 1);
		for (int i=1; i<nums.size(); i++) {
			for (int j=0; j<i; j++) {
				if (nums[i] > nums[j])
					dp[i] = max(dp[i], dp[j]+1);
			}
		}
		return dp;
	}

public:
	int minimumMountainRemovals(vector<int>& nums) {
		vector<int> incLen = LIS_using_BS(nums);
		reverse(nums.begin(), nums.end());
		vector<int> decLen = LIS_using_BS(nums);
		reverse(decLen.begin(), decLen.end());

		int mountainLen = 1;
		for (int i=1; i<nums.size()-1; i++) {
			if (incLen[i]>1 && decLen[i]>1)
				mountainLen = max(mountainLen, incLen[i]+decLen[i]-1);
		}
		return nums.size()-mountainLen;
	}
};



// ********** pure DP (Python) *********

class Solution:
	def minimumMountainRemovals(self, nums):
		n = len(nums)
		dp1, dp2 = [1]*n, [1]*n
		for i in range(1, n):
			for j in range(i):
				if nums[j] < nums[i]: dp1[i] = max(dp1[i], 1+dp1[j])
				if nums[j] > nums[i]:
					if dp1[j] > 1: dp2[i] = max(dp2[i], 1 + dp1[j])
					if dp2[j] > 1: dp2[i] = max(dp2[i], 1 + dp2[j])
		
		return n - max(dp2)