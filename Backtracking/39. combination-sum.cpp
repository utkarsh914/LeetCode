/*
https://leetcode.com/problems/combination-sum/

Given an array of distinct integers candidates and a target integer target,
return a list of all unique combinations of candidates where the chosen numbers sum to target.
You may return the combinations in any order.
The same number may be chosen from candidates an unlimited number of times.
Two combinations are unique if the frequency of at least one of the chosen numbers is different.
It is guaranteed that the number of unique combinations
that sum up to target is less than 150 combinations for the given input.

Example 1:
Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation:
2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
7 is a candidate, and 7 = 7.
These are the only two combinations.
*/

class Solution {
public:
	int currSum=0, targetSum=0;
	vector<int> currVec;
	vector<vector<int>> result;

	vector<vector<int>> combinationSum(vector<int>& cand, int target) {
		targetSum = target;
		backtrack(cand, 0);
		return result;
	}

	void backtrack(vector<int>& cand, int start) {
		if (currSum == targetSum)
			result.push_back(currVec);
		for (int i=start; i<cand.size(); i++) {
			if (currSum + cand[i] > targetSum)
				continue;
			int count = 0;
			// keep taking cur candidate as many times it can be taken
			while (currSum + cand[i] <= targetSum) {
				count++;
				currSum += cand[i];
				currVec.push_back(cand[i]);
				// backtrack on remaining part
				backtrack(cand, i+1);
			}
			while (count--) {
				// remove the ith element count times
				currSum -= cand[i];
				currVec.pop_back();
			}
		}
	}
};

// ******* IF AN ELEMENT CAN BE USED JUST ONCE ********
// ************** (combination sum ii) ****************
class Solution {
public:
	int currSum=0, targetSum=0;
	vector<int> currVec;
	vector<vector<int>> result;

	vector<vector<int>> combinationSum(vector<int>& cand, int target) {
		targetSum = target;
		backtrack(cand, 0);
		return result;
	}

	void backtrack(vector<int>& cand, int start) {
		if (currSum == targetSum)
			result.push_back(currVec);
		for (int i=start; i<cand.size(); i++) {
			if (currSum + cand[i] > targetSum)
				continue;
			// add current element to curr vector
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