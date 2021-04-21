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
		vector<int> candidates {1,2,3,4,5,6,7,8,9};
		backtrack(candidates, 0);
		return result;
	}

	void backtrack(vector<int>& cand, int start) {
		if (currSum==targetSum and currVec.size()==requiredCount)
			result.push_back(currVec);

		for (int i = start; i < cand.size(); i++) {
			if (currSum + cand[i] > targetSum)
				continue;
			currSum += cand[i];
			currVec.push_back(cand[i]);
			// backtrack on remaining part
			backtrack(cand, i+1);
			// remove the ith element
			currSum -= cand[i];
			currVec.pop_back();
		}
	}
};