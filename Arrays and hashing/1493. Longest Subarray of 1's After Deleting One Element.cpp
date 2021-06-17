// https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/

/*
Given a binary array nums, you should delete one element from it.

Return the size of the longest non-empty subarray containing only 1's in the resulting array.

Return 0 if there is no such subarray.

 

Example 1:

Input: nums = [1,1,0,1]
Output: 3
Explanation: After deleting the number in position 2, [1,1,1] contains 3 numbers
with value of 1's.
Example 2:

Input: nums = [0,1,1,1,0,1,1,0,1]
Output: 5
Explanation: After deleting the number in position 4, [0,1,1,1,1,1,0,1]
longest subarray with value of 1's is [1,1,1,1,1].
Example 3:

Input: nums = [1,1,1]
Output: 2
Explanation: You must delete one element.
Example 4:

Input: nums = [1,1,0,0,1,1,1,0,1]
Output: 4
Example 5:

Input: nums = [0,0,0]
Output: 0
 

Constraints:

1 <= nums.length <= 10^5
nums[i] is either 0 or 1.
*/










// maintain a sliding window with at most 1 zero in it
class Solution {
public:
	int longestSubarray(vector<int>& A) {
		int N = A.size(), ans = 0, zeroCount = 0;

		for (int i = 0, j = 0; j < N; j++) {
			if (A[j] == 0) zeroCount++;
			// delete from back until at most 1 zero remains
			while (zeroCount > 1) {
				if (A[i++] == 0) zeroCount--;
			}
			ans = max(ans, j-i+1 - 1);
			// if deleting an element was not compulsory
			// ans = max(ans, j-i+1 - zeroCount);
		}

		return ans;
	}
};






/*
prev[i] = length of longest contiguous '1's subarray ending at i
next[i] = length of longest contiguous '1's subarray starting from i

if we delete ith element, then prev[i-1] and next[i+1] will be combined
*/
class Solution {
public:
	int longestSubarray(vector<int>& A) {
		int N = A.size(), ans = 0;
		vector<int> prev(N), next(N);
		prev[0] = A[0] == 1;
		next[N-1] = A[N-1] == 1;
		// from left to right
		for (int i = 1; i < N; i++) {
			if (A[i] == 0) prev[i] = 0;
			else prev[i] = 1 + prev[i-1];
		}
		// from right to left
		for (int i = N-2; i >= 0; i--) {
			if (A[i] == 0) next[i] = 0;
			else next[i] = 1 + next[i+1];
		}

		// try deleting every index
		for (int i = 0; i < N; i++) {
			int L = i > 0 ? prev[i-1] : 0;
			int R = i+1 < N ? next[i+1] : 0;
			ans = max(ans, L + R);
		}

		return ans;
	}
};









// calculate prev[i] on the fly
class Solution {
public:
	int longestSubarray(vector<int>& A) {
		int N = A.size(), ans = 0;
		vector<int> next(N);
		next[N-1] = A[N-1] == 1;
		// from right to left
		for (int i = N-2; i >= 0; i--) {
			if (A[i] == 0) next[i] = 0;
			else next[i] = 1 + next[i+1];
		}

		// try deleting every index
		int L = 0;
		for (int i = 0; i < N; i++) {
			int R = i+1 < N ? next[i+1] : 0;
			ans = max(ans, L + R);
			// update left
			if (A[i] == 0) L = 0;
			else L = L + 1;
		}

		return ans;
	}
};