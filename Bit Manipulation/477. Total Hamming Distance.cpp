// https://leetcode.com/problems/total-hamming-distance/

/*
The Hamming distance between two integers is the number of positions
at which the corresponding bits are different.

Given an integer array nums, return the sum of Hamming distances
between all the pairs of the integers in nums.


Example 1:

Input: nums = [4,14,2]
Output: 6
Explanation: In binary representation, the 4 is 0100, 14 is 1110, and 2 is 0010 (just
showing the four bits relevant in this case).
The answer will be:
HammingDistance(4, 14) + HammingDistance(4, 2) + HammingDistance(14, 2) = 2 + 2 + 2 = 6.
Example 2:

Input: nums = [4,14,4]
Output: 4
 

Constraints:

1 <= nums.length <= 105
0 <= nums[i] <= 109
*/








/*
for n = 0 to 31,
count the number of ele having nth bit as 0, and 1

again for n = 0 to 31
for every number the count of nums having bits as opposite of cur
should be added to the answer
and, map[n][bit]-- is done to remove the cur num (so, we don't count it twice)
*/
class Solution {
public:
	int totalHammingDistance(vector<int>& A) {
		vector<array<int,2>> map(32, {0,0});
		int ans = 0;
		for (int n = 0; n < 32; n++) {
			for (int i = 0; i < A.size(); i++) {
				int bit = A[i] & (1 << n) ? 1 : 0;
				map[n][bit]++;
			}
		}

		for (int n = 0; n < 32; n++) {
			for (int i = 0; i < A.size(); i++) {
				int bit = A[i] & (1 << n) ? 1 : 0;
				ans += map[n][!bit];
				map[n][bit]--;
			}
		}

		return ans;
	}
};