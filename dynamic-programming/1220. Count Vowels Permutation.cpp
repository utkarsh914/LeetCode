// https://leetcode.com/problems/count-vowels-permutation/

/*
Given an integer n, your task is to count how many strings of length n can be formed under the following rules:

Each character is a lower case vowel ('a', 'e', 'i', 'o', 'u')
Each vowel 'a' may only be followed by an 'e'.
Each vowel 'e' may only be followed by an 'a' or an 'i'.
Each vowel 'i' may not be followed by another 'i'.
Each vowel 'o' may only be followed by an 'i' or a 'u'.
Each vowel 'u' may only be followed by an 'a'.
Since the answer may be too large, return it modulo 10^9 + 7.

 

Example 1:

Input: n = 1
Output: 5
Explanation: All possible strings are: "a", "e", "i" , "o" and "u".
Example 2:

Input: n = 2
Output: 10
Explanation: All possible strings are: "ae", "ea", "ei", "ia", "ie", "io", "iu", "oi", "ou" and "ua".
Example 3: 

Input: n = 5
Output: 68
 

Constraints:

1 <= n <= 2 * 10^4
*/








/*
Use dynamic programming.
Let dp[i][j] be the number of strings of length i that ends with the j-th vowel.
Deduce the recurrence from the given relations between vowels.
*/
class Solution {
public:
	int countVowelPermutation(int n) {
		unsigned int dp[n+1][5];
		dp[1][0] = dp[1][1] = dp[1][2] = dp[1][3] = dp[1][4] = 1;
		int m = 1e9+7;
		
		for (int i = 2; i <= n; i++) {
			dp[i][0] = (dp[i-1][1]) % m;
			dp[i][1] = (dp[i-1][0] + dp[i-1][2]) % m;
			dp[i][2] = (dp[i-1][0] + dp[i-1][1] + dp[i-1][3] + dp[i-1][4]) % m;
			dp[i][3] = (dp[i-1][2] + dp[i-1][4]) % m;
			dp[i][4] = (dp[i-1][0]) % m;
		}
		
		return (dp[n][0] + dp[n][1] + dp[n][2] + dp[n][3] + dp[n][4]) % m;
	}
};







class Solution {
public:
	int countVowelPermutation(int n) {
		unsigned int dp[2][5];
		dp[1][0] = dp[1][1] = dp[1][2] = dp[1][3] = dp[1][4] = 1;
		int m = 1e9+7;
		
		for (int i = 2; i <= n; i++) {
			int cur = i % 2, prev = (i + 1) % 2;
			dp[cur][0] = (dp[prev][1]) % m;
			dp[cur][1] = (dp[prev][0] + dp[prev][2]) % m;
			dp[cur][2] = (dp[prev][0] + dp[prev][1] + dp[prev][3] + dp[prev][4]) % m;
			dp[cur][3] = (dp[prev][2] + dp[prev][4]) % m;
			dp[cur][4] = (dp[prev][0]) % m;
		}
		
		int i = n % 2;
		return (dp[i][0] + dp[i][1] + dp[i][2] + dp[i][3] + dp[i][4]) % m;
	}
};