// https://leetcode.com/problems/jump-game-ii/
/*
Example 1:
Input: nums = [2,3,1,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2. Jump 1 step from index 0 to 1, then 3 steps to the last index.

Example 2:
Input: nums = [2,3,0,1,4]
Output: 2
*/

// dp={2,1,2,1,0}


// ********** more understandable *********
class Solution {
public:
	int jump(vector<int>& A) {
		if (A.size() <= 1) return 0;
		int ladder = A[0], stairs = A[0], jumps = 1;
		for (int level = 1; level < A.size(); level++) {
			if (level == A.size()-1) return jumps;
			ladder = max (ladder, level + A[level]);
			stairs--;
			if (stairs==0)
				jumps++, stairs = ladder - level;
		}
		return jumps;
	}
};

/*
class Solution {
public:
	int jump(vector<int>& nums) {
		int jumps = 0, curEnd = 0, curFarthest = 0;
		for (int i = 0; i < nums.size()-1; i++) {
			curFarthest = max(curFarthest, i + nums[i]);
			if (i == curEnd)
				jumps++, curEnd = curFarthest;
		}
		return jumps;
	}
};
*/