/*
https://leetcode.com/problems/subsets/

Given an integer array nums, return all possible subsets (the power set).
The solution set must not contain duplicate subsets.

Example 1:

Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
*/

/******  BACKTRACKING  *****/
class Solution {
public:
	vector<vector<int>> subsets(vector<int>& nums) {
		vector<vector<int>> result;
		vector<int> curr = {};
		backtrack(result, nums, curr, 0);
		return result;
	}

	void backtrack(vector<vector<int>>& result, vector<int>& nums, vector<int>& curr, int start) {
		result.push_back(curr);
		for (int i=start; i<nums.size(); i++) {
			curr.push_back(nums[i]);
			backtrack(result, nums, curr, i+1);
			curr.pop_back();
		}
	}
};

/******** bit manipulation ******/
class Solution {
public:
	vector<vector<int>> subsets(vector<int>& nums) {
		vector<vector<int>> result;
		int n = nums.size();
		for (int i=0; i<(1<<n); i++) {
			vector<int> temp;
			for (int j=0; j<n; j++) {
				if (i & (1<<j)) temp.push_back(nums[j]);
			}
			result.push_back(temp);
		}
		return result;
	}
};