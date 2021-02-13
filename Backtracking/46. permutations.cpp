/*
https://leetcode.com/problems/permutations/

Given an array nums of distinct integers, return all the possible permutations.
You can return the answer in any order.

Example 1:
Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
*/

class Solution {
public:

	vector<vector<int>> result;
	vector<bool> visited;
	vector<int> curr;

	vector<vector<int>> permute(vector<int>& nums) {
		visited = vector<bool> (nums.size(), false);
		backtrack(nums);
		return result;
	}

	void backtrack(vector<int>& nums) {
		if (curr.size() == nums.size())
			result.push_back(curr);
		for (int i=0; i<nums.size(); i++) {
			if (visited[i]) continue;
			curr.push_back(nums[i]); visited[i]=true;
			backtrack(nums);
			curr.pop_back(); visited[i]=false;
		}
	}
};

// ********** DFS BASED ************
void dfs(int pos, vector<int> &num, vector<vector<int>> &result) {
	if(pos == num.size()){
		result.push_back(num);
		return;
	}
	for (int i=pos; i<num.size(); i++) {
		swap(num[i], num[pos]);
		dfs(pos+1, num, result);
		swap(num[i], num[pos]);
	}
}