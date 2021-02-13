/*
https://leetcode.com/problems/permutations-ii/

Given a collection of numbers, nums, that might contain duplicates,
return all possible unique permutations in any order.

Example 1:
Input: nums = [1,1,2]
Output:
[[1,1,2],
 [1,2,1],
 [2,1,1]]



basically same as 'permulations' question.
The difficulty is to handle the duplicates.
With inputs as [1a, 1b, 2a],
If we don't handle the duplicates, the results would be: [1a, 1b, 2a], [1b, 1a, 2a]...,
so we must make sure 1a goes before 1b to avoid duplicates
By using nums[i-1]==nums[i] && !visited[i-1], we can make sure that 1b cannot be choosed before 1a
*/

class Solution {
public:
	vector<vector<int>> result;
	vector<bool> visited;
	vector<int> curr;

	vector<vector<int>> permuteUnique(vector<int>& nums) {
		visited = vector<bool> (nums.size(), false);
		sort(nums.begin(), nums.end()); // avoid dups
		backtrack(nums);
		return result;
	}

	void backtrack(vector<int>& nums) {
		if (curr.size() == nums.size()) {
			result.push_back(curr);
			return;
		}
		for (int i=0; i<nums.size(); i++) {
			if (visited[i]) continue;
			if (i>0 and nums[i]==nums[i-1] and !visited[i-1]) continue; // avoid dups
			curr.push_back(nums[i]); visited[i]=true;
			backtrack(nums);
			curr.pop_back(); visited[i]=false;
		}
	}
};
