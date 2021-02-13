class Solution {
public:

	int currSum=0, targetSum=0;
	vector<int> currVec;
	vector<vector<int>> result;
	
	vector<vector<int>> combinationSum2(vector<int>& nums, int target) {
		targetSum = target;
		sort(nums.begin(), nums.end());
		backtrack(nums, 0);
		return result;
	}

	void backtrack(vector<int>& nums, int start) {
		if (currSum == targetSum)
			result.push_back(currVec);
		for (int i=start; i<nums.size(); i++) {
			if (currSum+nums[i] > targetSum)
				return; // bcz further elements will be greater only
			if (i>0 and nums[i]==nums[i-1] and i>start)
				continue; // only different line to avoid dups
			currSum += nums[i];
			currVec.push_back(nums[i]);
			// backtrack on remaining part
			backtrack(nums, i+1);
			// remove the ith element
			currSum -= nums[i];
			currVec.pop_back();
		}
	}
};