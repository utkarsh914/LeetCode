// https://leetcode.com/problems/first-missing-positive/

// ********** naive *********
class Solution {
public:
	int firstMissingPositive(vector<int>& nums) {
		if (nums.empty()) return 1;
		unordered_set<int> set(nums.begin(), nums.end());
		int max_ = *max_element(nums.begin(), nums.end());
		max_ = max(max_, 1);
		for (int i=1; i<=max_; i++)
			if (!set.count(i))
				return i;
		return max_+1;
	}
};







// ******** O(n) time, O(1) space *******
class Solution {
public:
	int firstMissingPositive(vector<int>& nums) {
		
		if (nums.empty()) return 1;
		int maxNum = nums.size()+1;
		// ignore negative and greater nums
		for (int& n:nums) {
			if (n<=0 or n>=maxNum)
				n = 0;
		}

		for (int& n:nums) {
			int val = n % maxNum;
			if (val == 0) continue;
			nums[val-1] += maxNum;
		}

		for (int i=0; i<nums.size(); i++) {
			if (nums[i] < maxNum)
				return i+1;
		}
		
		return maxNum;
	}
};