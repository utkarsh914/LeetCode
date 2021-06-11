// https://leetcode.com/problems/single-element-in-a-sorted-array/




/*
You are given a sorted array consisting of only integers
where every element appears exactly twice,
except for one element which appears exactly once.
Find this single element that appears only once.

Follow up: Your solution should run in O(log n) time and O(1) space.

Example 1:

Input: nums = [1,1,2,3,3,4,4,8,8]
Output: 2
*/








/*
since all ele exist in pair, and A is sorted
elements are arranged like [aa bb cc dd ee] ....
it means, ele at every odd index is same as ele at its next even index
and, if this order is disturbed, it means single ele is at the left,
otherwise if order is fine, single ele is to the right

so, we can binary search the single element.

i^1 gives the corresponding pair of index for i
*/
class Solution {
public:
	int singleNonDuplicate(vector<int>& A) {
		int lo = 0, hi = A.size()-1;
		while (lo < hi) {
			int m = lo + (hi-lo)/2;
			if (A[m] != A[m^1])
				hi = m;
			else
				lo = m + 1;
		}
		return A[lo];
	}
};
/*
4 8 8
*/