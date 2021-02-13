/*
https://leetcode.com/problems/combination-sum-iii/

Find all valid combinations of k numbers that sum up to n such that the following conditions are true:
Only numbers 1 through 9 are used.
Each number is used at most once.
Return a list of all possible valid combinations.
The list must not contain the same combination twice, and the combinations may be returned in any order.

Example 1:
Input: k = 3, n = 7
Output: [[1,2,4]]
Explanation:
1 + 2 + 4 = 7
There are no other valid combinations.
*/

// ******* IF AN ELEMENT CAN BE USED JUST ONCE ********
// ************** (like combination sum i) ****************
class Solution {
public:
	int currSum=0, targetSum=0, requiredCount;
	vector<int> currVec;
	vector<vector<int>> result;

	vector<vector<int>> combinationSum3(int k, int n) {
		targetSum = n;
		requiredCount = k;
		vector<int> candidates;
		for (int i=1; i<=9; i++)
			candidates.push_back(i);
		backtrack(candidates, 0);
		return result;
	}

	void backtrack(vector<int>& candidates, int start) {
		if (currSum==targetSum and currVec.size()==requiredCount)
			result.push_back(currVec);
		for (int i=start; i<candidates.size(); i++) {
			if (currSum + candidates[i] > targetSum)
				continue;
			currSum += candidates[i];
			currVec.push_back(candidates[i]);
			// backtrack on remaining part
			backtrack(candidates, i+1);
			// remove the ith element
			currSum -= candidates[i];
			currVec.pop_back();
		}
	}
};