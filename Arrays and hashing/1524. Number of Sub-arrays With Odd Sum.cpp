// https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/

/*
Given an array of integers arr. Return the number of sub-arrays with odd sum.

As the answer may grow large, the answer must be computed modulo 10^9 + 7.


Example 1:

Input: arr = [1,3,5]
Output: 4
Explanation: All sub-arrays are [[1],[1,3],[1,3,5],[3],[3,5],[5]]
All sub-arrays sum are [1,4,9,3,8,5].
Odd sums are [1,9,3,5] so the answer is 4.
Example 2:

Input: arr = [2,4,6]
Output: 0
Explanation: All sub-arrays are [[2],[2,4],[2,4,6],[4],[4,6],[6]]
All sub-arrays sum are [2,6,12,4,10,6].
All sub-arrays have even sum and the answer is 0.
Example 3:

Input: arr = [1,2,3,4,5,6,7]
Output: 16
Example 4:

Input: arr = [100,100,99,99]
Output: 4
Example 5:

Input: arr = [7]
Output: 1
 

Constraints:

1 <= arr.length <= 10^5
1 <= arr[i] <= 100
*/





/*
-----  intuition: -----

# of evens doesn't matter for a subarr sum to become odd
only one condition is needed:
 -> count of odd nums should be odd in that subarr

now, if by taking ith ele, # of odds become even,
then A[i] can extend all the previous subarr that had odd # of odd elements

now, if by taking ith ele, # of odds become odd,
then A[i] can extend all the prev subarr that had even # of odd elements
*/
class Solution {
public:
	int numOfSubarrays(vector<int>& A) {
		long oddsTillNow = 0, evensTillNow = 1;
		long n = 0, ans = 0, mod = 1e9+7;

		for (int i = 0; i < A.size(); i++) {
			n += A[i] % 2 == 1; // count # of odds till now
			if (n % 2 == 1) {
				ans = (ans + evensTillNow) % mod;
				oddsTillNow++;
			} else {
				ans = (ans + oddsTillNow) % mod;
				evensTillNow++;
			}
		}

		return ans;
	}
};






/*
---- clearer ------

If we know the number of even and odd subarrays that end at the previous element,
we can figure out how many even and odd subarrays we have for element n:

1. If n is even, we increase the number of even subarrays;
	the number of odd subarrays does not change.

2. If n is odd, the number of odd subarrays is the previous number of even subarrays + 1.
	The number of even subarrays is the previous number of odd subarrays.


Looking at this example:

Array: [1, 1, 2, 1]  Total
Odd:	1  1  1  3	 6
Even:   0  1  2  1
*/

int numOfSubarrays(vector<int>& arr) {
	int odd = 0, even = 0, sum = 0;
	for (int n : arr) {
		if (n % 2 == 1) {
			swap(odd, even);
			++odd;
		}
		else ++even;
		sum = (sum + odd) % 1000000007;
	}

	return sum;
}
