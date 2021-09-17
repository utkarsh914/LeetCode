// https://leetcode.com/problems/k-concatenation-maximum-sum/

/*
Given an integer array arr and an integer k, modify the array by repeating it k times.

For example, if arr = [1, 2] and k = 3 then the modified array will be [1, 2, 1, 2, 1, 2].

Return the maximum sub-array sum in the modified array. Note that the length of the sub-array can be 0 and its sum in that case is 0.

As the answer can be very large, return the answer modulo 109 + 7.

 

Example 1:

Input: arr = [1,2], k = 3
Output: 9
Example 2:

Input: arr = [1,-2,1], k = 5
Output: 2
Example 3:

Input: arr = [-1,-2], k = 7
Output: 0
 

Constraints:

1 <= arr.length <= 105
1 <= k <= 105
-104 <= arr[i] <= 104
*/

class Solution {
public:
	int kConcatenationMaxSum(vector<int>& A, long k) {
		long sum = accumulate(A.begin(), A.end(), 0L);
		long prefix = 0, suffix = 0;
		long between = kadane(A);
		if (k == 1) return between;

		for (long i = 0, cursum = 0; i < A.size(); i++) {
			cursum += A[i];
			prefix = max(prefix, cursum);
		}
		for (long i = A.size()-1, cursum = 0; i >= 0; i--) {
			cursum += A[i];
			suffix = max(suffix, cursum);
		}

		return max({ between,
					sum * k,
					suffix + prefix,
					suffix + prefix + (k-2) * sum })
			% long(1e9+7);
	}

	long kadane(vector<int>& A) {
		long cursum = 0, maxsum = 0;
		for (long n : A) {
			cursum += n;
			maxsum = max(maxsum, cursum);
			if (cursum < 0) cursum = 0;
		}
		return maxsum;
	}
};









/*
doing essentially the same thing,
but more complicated.

It combined finding the value of (prefix + suffix)
*/
int kConcatenationMaxSum(vector<int>& arr, int k) {
	int n = arr.size(), sum = arr[0], mx = arr[0];
	int64_t total = accumulate(arr.begin(), arr.end(), 0), mod = 1e9+7;
	for (int i = 1; i < n * min(k, 2); i++) {
		sum = max(arr[i % n], sum + arr[i % n]);
		mx = max(mx, sum);
	}
	return max<int64_t>({0, mx, total * max(0, k - 2) + mx}) % mod;
}