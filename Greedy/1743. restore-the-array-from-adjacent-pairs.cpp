// https://leetcode.com/problems/restore-the-array-from-adjacent-pairs/

/*
There is an integer array nums that consists of n unique elements, but you have forgotten it. However, you do remember every pair of adjacent elements in nums.

You are given a 2D integer array adjacentPairs of size n - 1 where each adjacentPairs[i] = [ui, vi] indicates that the elements ui and vi are adjacent in nums.

It is guaranteed that every adjacent pair of elements nums[i] and nums[i+1] will exist in adjacentPairs, either as [nums[i], nums[i+1]] or [nums[i+1], nums[i]]. The pairs can appear in any order.

Return the original array nums. If there are multiple solutions, return any of them.

Example 1:

Input: adjacentPairs = [[2,1],[3,4],[3,2]]
Output: [1,2,3,4]
Explanation: This array has all its adjacent pairs in adjacentPairs.
Notice that adjacentPairs[i] may not be in left-to-right order.
*/




/*
For each number, record its neighbours using a hash map.
The number with only one neighbour is the head (or the tail) of the list.
Find the head, and keep going.
*/

class Solution {
public:
	vector<int> restoreArray(vector<vector<int>>& pairs) {
		unordered_map<int, set<int>> g;
		vector<int> ans;
		int n = pairs.size()+1;
		
		for (auto& p: pairs) {
			int u = p[0], v = p[1];
			g[u].insert(v);
			g[v].insert(u);
		}
		
		int prev = -1;
		for (auto& p : g) {
			if (p.second.size() == 1) {
				prev = p.first;
				break;
			}
		}

		while (ans.size() < n) {
			ans.push_back(prev);
			int u = prev, v = *(g[u].begin());
			g.erase(u);
			g[v].erase(u);
			prev = v;
		}

		return ans;
	}
};