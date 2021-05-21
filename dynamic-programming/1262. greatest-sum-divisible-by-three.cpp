// https://leetcode.com/problems/greatest-sum-divisible-by-three/

/*
Given an array nums of integers, we need to find the maximum possible sum
of elements of the array such that it is divisible by three.


Example 1:

Input: nums = [3,6,5,1,8]
Output: 18
Explanation: Pick numbers 3, 6, 1 and 8 their sum is 18 (maximum sum divisible by 3).
Example 2:

Input: nums = [4]
Output: 0
Explanation: Since 4 is not divisible by 3, do not pick any number.
Example 3:

Input: nums = [1,2,3,4,4]
Output: 12
Explanation: Pick numbers 1, 3, 4 and 4 their sum is 12 (maximum sum divisible by 3).
*/






/*

Represent the state as DP[pos][mod]:
maximum possible sum starting in the position "pos" in the array
where the current sum modulo 3 is equal to mod.


dp[0] = largest sum which is divisible by 3
dp[1] = largest sum when divided by 3, remainder = 1
dp[2] = largest sum when divided by 3, remainder = 2
*/
class Solution {
public:
	int maxSumDivThree(vector<int>& A) {
		vector<vector<int>> dp(A.size()+1, vector<int> (3));

		for (int i = A.size()-1; i >= 0; i--) {
			int n = A[i];
			// copy prev row
			// it handles the case of not taking the curr element
			for (int j = 0; j < 3; j++) {
				dp[i][j] = dp[i+1][j];
			}
			// take every element of prev row, and add n to it
			// then place it to correct spot in curr row
			for (int j = 0; j < 3; j++) {
				int ind = (n + dp[i+1][j]) % 3;
				dp[i][ind] = max(dp[i][ind], n + dp[i+1][j]);
			}
		}

		return dp[0][0];
	}
};




class Solution {
public:
	int maxSumDivThree(vector<int>& A) {
		vector<vector<int>> dp(2, vector<int> (3));

		for (int i = A.size()-1; i >= 0; i--) {
			int n = A[i];
			// copy prev row
			// it handles the case of not taking the curr element
			for (int j = 0; j < 3; j++) {
				dp[i % 2][j] = dp[(i+1) % 2][j];
			}
			// take every element of prev row, and add n to it
			// then place it to correct spot in curr row
			for (int j = 0; j < 3; j++) {
				int ind = (n + dp[(i+1) % 2][j]) % 3;
				dp[i % 2][ind] = max(dp[i % 2][ind], n + dp[(i+1) % 2][j]);
			}
		}

		return dp[0][0];
	}
};



	int maxSumDivThree(vector<int>& A) {
		vector<int> dp(3);
		for (int a : A)
			for (int i : vector<int>(dp))
				dp[(i + a) % 3] = max(dp[(i + a) % 3], i + a);
		return dp[0];
	}