// https://leetcode.com/problems/binary-trees-with-factors/

/*
Given an array of unique integers, arr, where each integer arr[i] is strictly greater than 1.
We make a binary tree using these integers, and each number may be used for any number of times.
Each non-leaf node's value should be equal to the product of the values of its children.
Return the number of binary trees we can make.
The answer may be too large so return the answer modulo 109 + 7.

Example 1:

Input: arr = [2,4]
Output: 3
Explanation: We can make these trees: [2], [4], [4, 2, 2]
*/



/*
Sort the list A at first. Scan A from small element to bigger.

DP equation:
dp[i] = sum(dp[j] * dp[i / j])
res = sum(dp[i])
with i, j, i / j in the list L
*/
class Solution {
public:
	int numFactoredBinaryTrees(vector<int>& A) {
		long res = 0, mod = pow(10, 9) + 7;
		sort(A.begin(), A.end());
		unordered_map<int, long> dp;
		for (int i = 0; i < A.size(); ++i) {
			dp[A[i]] = 1;
			for (int j = 0; j < i; ++j)
				if (A[i] % A[j] == 0)
					dp[A[i]] = (dp[A[i]] + dp[A[j]] * dp[A[i] / A[j]]) % mod;
			res = (res + dp[A[i]]) % mod;
		}
		return res;
	}
};

