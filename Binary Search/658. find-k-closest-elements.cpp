// https://leetcode.com/problems/find-k-closest-elements/

/*
Given a sorted integer array arr, two integers k and x,
return the k closest integers to x in the array.
The result should also be sorted in ascending order.

An integer a is closer to x than an integer b if:

|a - x| < |b - x|, or
|a - x| == |b - x| and a < b
 

Example 1:

Input: arr = [1,2,3,4,5], k = 4, x = 3
Output: [1,2,3,4]
Example 2:

Input: arr = [1,2,3,4,5], k = 4, x = -1
Output: [1,2,3,4]
*/








/*
Intuition -

The array is sorted.
If we want find the one number closest to x,
we don't have to check one by one.
it's straightforward to use binary research.

Now we want the k closest,
the logic should be similar.


If x - A[mid] > A[mid + k] - x,
it means A[mid + 1] ~ A[mid + k] is better than A[mid] ~ A[mid + k - 1],
and we have mid smaller than the right i.
So assign left = mid + 1.

Important -
Note that, you SHOULD NOT compare the absolute value of abs(x - A[mid]) and abs(A[mid + k] - x).
It fails at cases like A = [1,1,2,2,2,2,2,3,3], x = 3, k = 3
*/
class Solution {
public:
	vector<int> findClosestElements(vector<int>& A, int k, int x) {
		
		int lo = 0, hi = A.size()-k;
		while (lo < hi) {
			int mid = lo + (hi - lo) / 2;
			if (-(A[mid]-x) > A[mid+k]-x)
				lo = mid + 1;
			else
				hi = mid;
		}

		return vector<int> (A.begin()+lo, A.begin()+lo+k);
	}
};
