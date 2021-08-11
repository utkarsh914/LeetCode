// https://leetcode.com/problems/split-array-with-same-average/


// TLE
class Solution {
	unordered_map<int, unordered_map<int,bool>> dp;
public:
	bool splitArraySameAverage(vector<int>& nums) {
		return canSplit(nums, 0, 0, 0);
	}
	
	bool canSplit(vector<int>& A, int i, int mask1, int mask2) {
		if (i == A.size()) return checkAvg(A, mask1, mask2);
		if (dp[mask1].count(mask2)) return dp[mask1][mask2];
		bool p1 = canSplit(A, i + 1, mask1 | (1<<i), mask2);
		bool p2 = canSplit(A, i + 1, mask1, mask2 | (1 << i));
		return dp[mask1][mask2] = p1 or p2;
	}
	
	inline bool checkAvg(vector<int>& A, int mask1, int mask2) {
		double sum1 = 0, n1 = 0, sum2 = 0, n2 = 0;
		for (int i = 0; i < 31; i++) {
			if (mask1 & (1<<i)) sum1 += A[i], n1+=1;
			if (mask2 & (1<<i)) sum2 += A[i], n2+=1;
		}
		if (n1 == 0 or n2 == 0) return false;
		double avg1 = sum1 / n1, avg2 = sum2 / n2;
		return (abs(avg1 - avg2) < 1e-3);
	}
};





/*
------- TLE -------

use only mask1.
rest bits automatically means they're set in mask2
*/
class Solution {
	unordered_map<int, unordered_map<int,bool>> dp;
public:
	bool splitArraySameAverage(vector<int>& nums) {
		return canSplit(nums, 0, 0, 0);
	}
	
	bool canSplit(vector<int>& A, int i, int mask1) {
		if (i == A.size()) return checkAvg(A, mask1);
		if (dp.count(mask1)) return dp[mask1];
		bool p1 = canSplit(A, i + 1, mask1 | (1<<i));
		bool p2 = canSplit(A, i + 1, mask1);
		return dp[mask1] = p1 or p2;
	}
	
	inline bool checkAvg(vector<int>& A, int mask1) {
		double sum1 = 0, n1 = 0, sum2 = 0, n2 = 0;
		for (int i = 0; i < A.size(); i++) {
			if (mask1 & (1<<i)) sum1 += A[i], n1+=1;
			else sum2 += A[i], n2+=1;
		}
		if (n1 == 0 or n2 == 0) return false;
		double avg1 = sum1 / n1, avg2 = sum2 / n2;
		return (abs(avg1 - avg2) < 1e-3);
	}
};