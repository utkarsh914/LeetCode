// https://leetcode.com/problems/max-consecutive-ones-iii/

/*
Given a binary array nums and an integer k,
return the maximum number of consecutive 1's in the array
if you can flip at most k 0's.

Example 1:

Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
Output: 6
Explanation: [1,1,1,0,0,1,1,1,1,1,1]
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.
*/




/*
======== SAME AS: 3. longest-substring-without-repeating-characters =======
*/
class Solution {
public:
	int longestOnes(vector<int>& A, int K) {
		int ans = 0, nz = 0;
		for (int l = 0, r = 0; r < A.size(); r++) {
			nz += !A[r];
			while (nz > K) {
				nz -= !A[l++];
			}
			ans = max(ans, r-l+1);
		}
		return ans;
	}
};