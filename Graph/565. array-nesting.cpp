// https://leetcode.com/problems/array-nesting/

class Solution {
public:
	int arrayNesting(vector<int>& nums) {
		vector<bool> taken(nums.size(), false);
		int maxSize = 1;

		for (int n:nums) {
			if (taken[n]) continue;

			int curSize = 1;
			int prev = n; taken[n]=true;
			while (true) {
				if (taken[nums[prev]]) break;
				else prev = nums[prev], curSize++;
				taken[prev] = true;
			}

			maxSize = max(maxSize, curSize);
		}

		return maxSize;
	}
};