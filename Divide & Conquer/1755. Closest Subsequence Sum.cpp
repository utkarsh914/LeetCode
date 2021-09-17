// https://leetcode.com/problems/closest-subsequence-sum/

/*
You are given an integer array nums and an integer goal.

You want to choose a subsequence of nums such that the sum of its elements is the closest possible to goal. That is, if the sum of the subsequence's elements is sum, then you want to minimize the absolute difference abs(sum - goal).

Return the minimum possible value of abs(sum - goal).

Note that a subsequence of an array is an array formed by removing some elements (possibly all or none) of the original array.

 

Example 1:

Input: nums = [5,-7,3,5], goal = 6
Output: 0
Explanation: Choose the whole array as a subsequence, with a sum of 6.
This is equal to the goal, so the absolute difference is 0.
Example 2:

Input: nums = [7,-9,15,-2], goal = -5
Output: 1
Explanation: Choose the subsequence [7,-9,-2], with a sum of -4.
The absolute difference is abs(-4 - (-5)) = abs(1) = 1, which is the minimum.
Example 3:

Input: nums = [1,2,3], goal = -7
Output: 7
 

Constraints:

1 <= nums.length <= 40
-107 <= nums[i] <= 107
-109 <= goal <= 109
*/





// TLE (due to large constraint of goal)
class Solution {
	unordered_map<int,int> dp[41] = {};
public:
	int minAbsDifference(vector<int>& nums, int goal) {
		return pick(nums, 0, goal);
	}
	
	int pick(vector<int>& nums, int i, int goal) {
		if (i == nums.size()) return abs(goal);
		if (dp[i].count(goal)) return dp[i][goal];
		return dp[i][goal] = min(
			pick(nums, i+1, goal - nums[i]),
			pick(nums, i+1, goal)
		);
	}
};








/*
Divide the array into two parts of nearly is equal size.
Consider all subsets of one part and make a list of all possible subset sums and sort this list.

Consider all subsets of the other part, and for each one,
let its sum = x, do binary search to get the nearest possible value to goal - x
in the first part.
or use 2 pointer method
*/
class Solution {
	int diff;
public:
	int minAbsDifference(vector<int>& nums, int goal) {
		diff = abs(goal);
		pick(nums, 0, nums.size()-1, goal);
		return diff;
	}
	
	void pick(vector<int>& nums, int lo, int hi, int goal) {

		if (lo == hi) {
			diff = min(diff, abs(nums[lo] - goal));
			return;
		}

		int mid = (lo + hi) / 2;
		pick(nums, lo, mid, goal);
		pick(nums, mid+1, hi, goal);

		int lsize = mid - lo + 1, rsize = hi - mid;
		int lsumSize = 1 << lsize, rsumSize = 1 << rsize;
		int lsums[lsumSize], rsums[rsumSize];
		
		
		// find all subset sums of left subarray
		for (int i = 0; i < lsumSize; i++) {
			int sum = 0;
			for (int j = 0; j < lsize; j++)
				if (i & (1 << j))
					sum += nums[lo + j];
			lsums[i] = sum;
		}

		// find all subset sums of right subarray
		for (int i = 0; i < rsumSize; i++) {
			int sum = 0;
			for (int j = 0; j < rsize; j++)
				if (i & (1 << j))
					sum += nums[mid + 1 + j];
			rsums[i] = sum;
		}

		// pick two elements from both sum arrays
		// such that they are closest to goal
		
		sort(lsums, lsums + lsumSize);
		sort(rsums, rsums + rsumSize);

		for (int i = 0, j = rsumSize - 1; i < lsumSize and j >= 0; ) {
			diff = min(diff, abs(lsums[i] + rsums[j] - goal)); // update min diff
			if (lsums[i] + rsums[j] <= goal) i++;
			else j--;
		}

	}
};