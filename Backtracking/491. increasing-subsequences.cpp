// https://leetcode.com/problems/increasing-subsequences/

/*
Given an integer array, your task is to find all the different possible increasing subsequences of the given array,
and the length of an increasing subsequence should be at least 2.

Example:
Input: [4, 6, 7, 7]
Output: [[4, 6], [4, 7], [4, 6, 7], [4, 6, 7, 7], [6, 7], [6, 7, 7], [7,7], [4,7,7]]

Constraints:
The length of the given array will not exceed 15.
The range of integer in the given array is [-100,100].
The given array may contain duplicates, and two equal integers should also be considered as a special case of increasing sequence.
*/

class Solution {

	vector<vector<int>> ans;
	vector<int> curr;

	void backtrack(vector<int>& nums, int start, int prev=INT_MIN) {
		if (curr.size() >= 2)
			ans.push_back(curr);

		unordered_set<int> used;
		for (int i=start; i<nums.size(); i++) {
			if (nums[i] < prev or used.count(nums[i])) continue;
			used.insert(nums[i]);
			curr.push_back(nums[i]);
			backtrack(nums, i+1, nums[i]);
			curr.pop_back();
		}
	}

public:
	vector<vector<int>> findSubsequences(vector<int>& nums) {
		backtrack(nums, 0, INT_MIN);
		return ans;
	}
};



// ****** using global set *******
class Solution {
	
	set<vector<int>> st;
	vector<int> curr;

	void backtrack(vector<int>& nums, int start, int prev=INT_MIN) {
		if (curr.size() >= 2)
			st.insert(curr);
		for (int i=start; i<nums.size(); i++) {
			if (nums[i] < prev) continue;
			curr.push_back(nums[i]);
			backtrack(nums, i+1, nums[i]);
			curr.pop_back();
		}
	}

public:
	vector<vector<int>> findSubsequences(vector<int>& nums) {
		backtrack(nums, 0, INT_MIN);
		return vector<vector<int>> (st.begin(), st.end());
	}
};