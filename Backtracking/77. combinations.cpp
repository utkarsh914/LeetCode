/*
https://leetcode.com/problems/combinations/

Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.
You may return the answer in any order.

Example 1:

Input: n = 4, k = 2
Output:
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
*/

class Solution {
public:

	int requiredCount;
	vector<vector<int>> result;
	vector<int> currVec;

	vector<vector<int>> combine(int n, int k) {
		requiredCount = k;
		backtrack(1, n);
		return result;
	}

	void backtrack(int start, int end) {
		if (currVec.size()==requiredCount) {
			result.push_back(currVec);
			return;
		}
		for (int i=start; i<=end; i++) {
			currVec.push_back(i);
			backtrack(i+1, end);
			currVec.pop_back();
		}
	}
};