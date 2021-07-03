// https://leetcode.com/problems/number-of-ways-to-rearrange-sticks-with-k-sticks-visible/

/*
There are n uniquely-sized sticks whose lengths are integers from 1 to n. You want to arrange the sticks such that exactly k sticks are visible from the left. A stick is visible from the left if there are no longer sticks to the left of it.

For example, if the sticks are arranged [1,3,2,5,4], then the sticks with lengths 1, 3, and 5 are visible from the left.
Given n and k, return the number of such arrangements. Since the answer may be large, return it modulo 109 + 7.

 

Example 1:

Input: n = 3, k = 2
Output: 3
Explanation: [1,3,2], [2,3,1], and [2,1,3] are the only arrangements such that exactly 2 sticks are visible.
The visible sticks are underlined.
Example 2:

Input: n = 5, k = 5
Output: 1
Explanation: [1,2,3,4,5] is the only arrangement such that all 5 sticks are visible.
The visible sticks are underlined.
Example 3:

Input: n = 20, k = 11
Output: 647427950
Explanation: There are 647427950 (mod 109 + 7) ways to rearrange the sticks such that exactly 11 sticks are visible.
 

Constraints:

1 <= n <= 1000
1 <= k <= n
*/








/*
Explanation
For case that n stick to see k from left,
we considering the last element in the list:
case 1: if it's the largest,
then n-1 stick to see k-1 (excluding the last).
dp[n][k] += dp[n - 1][k - 1]

case 2: if it's not the largest,
n - 1 choices for the last elements
then n-1 stick to see k (excluding the last).
dp[n][k] += dp[n - 1][k] * (n - 1)

Edge case 1
if n == k, return 1;
Edge case 2
if k == 0, return 0;
*/
class Solution {
	int dp[1001][1001] = {}, mod = 1e9+7;
public:
	int rearrangeSticks(long n, long k) {
		if (n == k) return 1; // base case
		if (k == 0) return 0; // can't select zero visible sticks
		if (dp[n][k] != 0) return dp[n][k];

		// select the tallest stick
		long takeTallest = rearrangeSticks(n-1, k-1);
		// select any of the n - 1 sticks that are not the tallest
		long notTakeTallest = (n - 1) * rearrangeSticks(n - 1, k);
		// ans is sum of both ways
		return dp[n][k] = (takeTallest + notTakeTallest) % mod;
	}
};

