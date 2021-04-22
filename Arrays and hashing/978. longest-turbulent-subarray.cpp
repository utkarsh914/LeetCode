// https://leetcode.com/problems/longest-turbulent-subarray/

/*
Given an integer array arr, return the length of a maximum size turbulent subarray of arr.

A subarray is turbulent if the comparison sign flips between each adjacent pair of elements in the subarray.

More formally, a subarray [arr[i], arr[i + 1], ..., arr[j]] of arr is said to be turbulent if and only if:

For i <= k < j:
arr[k] > arr[k + 1] when k is odd, and
arr[k] < arr[k + 1] when k is even.
Or, for i <= k < j:
arr[k] > arr[k + 1] when k is even, and
arr[k] < arr[k + 1] when k is odd.
 

Example 1:

Input: arr = [9,4,2,10,7,8,8,1,9]
Output: 5
Explanation: arr[1] > arr[2] < arr[3] > arr[4] < arr[5]
Example 2:

Input: arr = [4,8,12,16]
Output: 2
*/






class Solution {
public:
	int maxTurbulenceSize(vector<int>& A) {
		int sign = 0, l = 1, maxl = 1;

		for (int i=1; i < A.size(); i++) {

			int cursign = signum(A[i-1]-A[i]);
			if (cursign == 0) l = 1;
			else if (cursign != sign) l++;
			else l = 2;

			maxl = max(l, maxl);
			sign = cursign;
		}

		return maxl;
	}
	
	int signum(int x) {
		if (x==0) return 0;
		return x < 0 ? -1 : 1;
	}
};







/*
We use the counter (cnt) to track subarray size.
Our counter is positive if we expect '>', and '<' otherwise.
Obviously, for each turn we flip the sign.

If the comparison matches the counter sign (e.g. A[i] > A[i + 1] and cnt > 0 ),
we increment (or decrement the negative) counter.
Otherwise, we reset the counter to 1 (or -1).
One edge case here is when two numbers are equal.
We set the counter to zero in this case.
*/
int maxTurbulenceSize(vector<int>& A, int res = 0) {
	for (auto i = 0, cnt = 0; i + 1 < A.size(); ++i, cnt *= -1) {
		if (A[i] > A[i + 1]) cnt = cnt > 0 ? cnt + 1 : 1;
		else if (A[i] < A[i + 1]) cnt = cnt < 0 ? cnt - 1 : -1;
		else cnt = 0;
		res = max(res, abs(cnt));
	}
	return res + 1;
}








// DP
	int maxTurbulenceSize(vector<int>& A) {
		vector<vector<int>> dp(A.size(), vector<int>(2, 1));
		int res = 1;
		for (int i = 1; i < A.size(); i++) {
			if (A[i] > A[i - 1])
				dp[i][0] = dp[i - 1][1] + 1;
			else if (A[i] < A[i - 1]) 
				dp[i][1] = dp[i - 1][0] + 1;
			res = max(res, max(dp[i][0], dp[i][1]));	 
		}
		return res;
	}










/*
TWO POINTERS
*/
class Solution:
	def maxTurbulenceSize(self, A: List[int]) -> int:
		if not A:
			return 0 

		nums = len(A)
		max_len = 1

		// # +1: prev element > current element
		// # -1: prev element < current element
		// # 0: prev element == current element
		prev, l = 2, 0
		for r in range(0, nums - 1):
			curr = 1 if A[r] > A[r + 1] else -1 if A[r] < A[r + 1] else 0

			// # in case previous comparison sign is the same as current or 
			// # previous flip sign is 0, we need to shrink window such that left
			// # point is advanced to the right pointer
			if curr == prev or not prev:
				l = r

			// # update variable to record previous comparison sign
			prev = curr

			// # as long as current comparison sign is not equal ("==")
			// # we should update our answer
			if curr:
				max_len = max(max_len, r - l + 2)

		return max_len