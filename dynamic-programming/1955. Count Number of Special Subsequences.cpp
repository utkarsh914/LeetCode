// https://leetcode.com/problems/count-number-of-special-subsequences/

/*
A sequence is special if it consists of a positive number of 0s, followed by a positive number of 1s, then a positive number of 2s.

For example, [0,1,2] and [0,0,1,1,1,2] are special.
In contrast, [2,1,0], [1], and [0,1,2,0] are not special.
Given an array nums (consisting of only integers 0, 1, and 2), return the number of different subsequences that are special. Since the answer may be very large, return it modulo 109 + 7.

A subsequence of an array is a sequence that can be derived from the array by deleting some or no elements without changing the order of the remaining elements. Two subsequences are different if the set of indices chosen are different.

 

Example 1:

Input: nums = [0,1,2,2]
Output: 3
Explanation: The special subsequences are [0,1,2,2], [0,1,2,2], and [0,1,2,2].
Example 2:

Input: nums = [2,2,0,0]
Output: 0
Explanation: There are no special subsequences in [2,2,0,0].
Example 3:

Input: nums = [0,1,2,0,1,2]
Output: 7
Explanation: The special subsequences are:
- [0,1,2,0,1,2]
- [0,1,2,0,1,2]
- [0,1,2,0,1,2]
- [0,1,2,0,1,2]
- [0,1,2,0,1,2]
- [0,1,2,0,1,2]
- [0,1,2,0,1,2]
 

Constraints:

1 <= nums.length <= 105
0 <= nums[i] <= 2
*/






/*
First solve a simpler problem

1. Counting the number of subsequences with 1s followed by 0s.
2. keep track of the partially matched subsequences to help us find the answer.
*/
class Solution {
public:
	int countSpecialSubsequences(vector<int>& nums) {
		long N = nums.size(), m = 1e9+7;
		vector<long> zero(N+1, 0); // # of subseq having 0's till now
		vector<long> zeroOne(N+1, 0); // # of subseq having 0's followed by 1's till now
		vector<long> zeroOneTwo(N+1, 0); // 0's followed by 1's, then 2's till now
		
		for (int i = 1; i <= N; i++) {
			if (nums[i-1] == 0)
				zero[i] = (zero[i-1] * 2L + 1L) % m;
			else zero[i] = zero[i-1];
		}
		
		for (int i = 1; i <= N; i++) {
			if (nums[i-1] == 1) {
				// can just append current '1' to all prev [0,0...1,1]
				// so total equals them plus them appended by current '1'
				zeroOne[i] = (2L * zeroOne[i-1]) % m;
				// append '1' to all previous [0,0...] subseq
				// so total equals all prev [0,0,...]
				zeroOne[i] = (zeroOne[i] + zero[i-1]) % m;
			}
			else zeroOne[i] = zeroOne[i-1];
		}
		
		for (int i = 1; i <= N; i++) {
			if (nums[i-1] == 2) {
				// similar logic as above
				zeroOneTwo[i] = (2L * zeroOneTwo[i-1]) % m;
				zeroOneTwo[i] = (zeroOneTwo[i] + zeroOne[i-1]) % m;
			}
			else zeroOneTwo[i] = zeroOneTwo[i-1];
		}
		
		return zeroOneTwo.back();
	}
};
/*
[0,1,2,0,1,2] - nums
[0,1,1,1,2,2] - zeros
[0,1,1,1,5,5] - zero_one
[0,0,1,1,1,7] - zero_one_two
*/