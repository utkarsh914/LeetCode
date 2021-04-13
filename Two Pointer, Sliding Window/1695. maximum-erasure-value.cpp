// https://leetcode.com/problems/maximum-erasure-value/

/*
You are given an array of positive integers nums
and want to erase a subarray containing unique elements.
The score you get by erasing the subarray is equal to the sum of its elements.
Return the maximum score you can get by erasing exactly one subarray.

An array b is called to be a subarray of a if it forms a contiguous subsequence of a,
that is, if it is equal to a[l],a[l+1],...,a[r] for some (l,r).

Example 1:

Input: nums = [4,2,4,5,6]
Output: 17
Explanation: The optimal subarray here is [2,4,5,6].
*/





/*
======== SAME AS: 3. longest-substring-without-repeating-characters =======

The main point here is for the subarray to contain unique elements for each index.
Only the first subarrays starting from that index have unique elements.
This can be solved using the two pointers technique
*/
class Solution {
public:
	int maximumUniqueSubarray(vector<int>& A) {
		int maxSum = 0, curSum = 0;
		unordered_set<int> set;

		for (int l = 0, r = 0; r < A.size(); r++) {
			while (set.count(A[r])) {
				curSum -= A[l];
				set.erase(A[l++]);
			}
			curSum += A[r];
			set.insert(A[r]);
			maxSum = max(maxSum, curSum);
		}

		return maxSum;
	}
};


// use array instead of set
class Solution {
public:
	int maximumUniqueSubarray(vector<int>& A) {
		int maxSum = 0, curSum = 0;
		bool set[10002] = {};

		for (int l = 0, r = 0; r < A.size(); r++) {
			while (set[A[r]] == true) {
				curSum -= A[l];
				set[A[l++]] = false;
			}
			curSum += A[r];
			set[A[r]] = true;
			maxSum = max(maxSum, curSum);
		}

		return maxSum;
	}
};