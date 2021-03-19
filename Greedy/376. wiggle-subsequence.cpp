// https://leetcode.com/problems/wiggle-subsequence/

/*
Given an integer array nums, return the length of the longest wiggle sequence.

A wiggle sequence is a sequence where the differences between successive numbers strictly alternate between positive and negative. The first difference (if one exists) may be either positive or negative. A sequence with fewer than two elements is trivially a wiggle sequence.

For example, [1, 7, 4, 9, 2, 5] is a wiggle sequence because the differences (6, -3, 5, -7, 3) are alternately positive and negative.
In contrast, [1, 4, 7, 2, 5] and [1, 7, 4, 5, 5] are not wiggle sequences, the first because its first two differences are positive and the second because its last difference is zero.
A subsequence is obtained by deleting some elements (eventually, also zero) from the original sequence, leaving the remaining elements in their original order.

Example 1:

Input: nums = [1,7,4,9,2,5]
Output: 6
Explanation: The entire sequence is a wiggle sequence.
Example 2:

Input: nums = [1,17,5,10,13,15,10,5,16,8]
Output: 7
Explanation: There are several subsequences that achieve this length. One is [1,17,10,13,10,16,8].
Example 3:

Input: nums = [1,2,3,4,5,6,7,8,9]
Output: 2

Constraints:

1 <= nums.length <= 1000
0 <= nums[i] <= 1000
*/


class Solution {
public:
	int wiggleMaxLength(vector<int>& nums) {
		// create an array which doesn't contain adjacent duplicates
		vector<int> n{nums[0]};
		for (int i=1; i<nums.size(); i++)
			if (nums[i]!=nums[i-1]) n.push_back(nums[i]);

		int s = n.size();
		if (s <= 2) return s;
		
		int count = 2, last = n[1], sign = signum(n[1]-n[0]);

		for (int i = 2; i < s; i++) {
			int curSign = signum(n[i]-last);
			if (curSign == 0) continue;
			if (curSign == sign) {
				if (sign > 0) last = max(last, n[i]);
				else if (sign < 0) last = min(last, n[i]);
			}
			else {
				count++;
				sign = curSign;
				last = n[i];
			}
		}
		
		return count;
	}
	
	int signum(int x) {
		if (x == 0) return 0;
		else return x>0 ? 1 : -1;
	}
};







