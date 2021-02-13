// https://leetcode.com/problems/previous-permutation-with-one-swap/

/*
Given an array of positive integers arr (not necessarily distinct),
return the lexicographically largest permutation that is smaller than arr,
that can be made with exactly one swap (A swap exchanges the positions of two numbers arr[i] and arr[j]).
If it cannot be done, then return the same array.

Example 1:

Input: arr = [3,2,1]
Output: [3,1,2]
Explanation: Swapping 2 and 1.
Example 2:

Input: arr = [1,1,5]
Output: [1,1,5]
Explanation: This is already the smallest permutation.
Example 3:

Input: arr = [1,9,4,6,7]
Output: [1,7,4,6,9]
Explanation: Swapping 9 and 7.
Example 4:

Input: arr = [3,1,1,3]
Output: [1,3,1,3]
Explanation: Swapping 1 and 3.
*/


/*
If the array is already sorted the solution is the input array.
If not, move form right side of array toward left side until the point where the left element is larger than right element.
At this point the left element (let's call it candid) is one of the elements that should be swapped.
But to swap with what element?
We actually need to swap candid with the largest value on its right side that is less than candid (let's call it candid_2).
Since the elements on the right side of candid are all sorted
we can find the largest smaller number than candid in O(logN) by binary search
*/

class Solution {
public:
	vector<int> prevPermOpt1(vector<int>& p) {
		int i = p.size()-2;
		while (i>=0 && p[i]<=p[i+1]) i--;
		if (i < 0) return p;

		int j = p.size()-1;
		while (j>i && p[j]>=p[i]) j--;
		// if it has dups, we'll take the leftmost dup
		// so that we make the largest possible permutation
		while (j-1>i && p[j-1]==p[j]) j--;
		swap(p[i], p[j]);

		return p;
	}
};