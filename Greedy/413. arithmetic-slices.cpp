// https://leetcode.com/problems/arithmetic-slices/

/*
A sequence of numbers is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.

For example, these are arithmetic sequences:

1, 3, 5, 7, 9
7, 7, 7, 7
3, -1, -5, -9
The following sequence is not arithmetic.

1, 1, 2, 5, 7
 
A zero-indexed array A consisting of N numbers is given. A slice of that array is any pair of integers (P, Q) such that 0 <= P < Q < N.

A slice (P, Q) of the array A is called arithmetic if the sequence:
A[P], A[P + 1], ..., A[Q - 1], A[Q] is arithmetic. In particular, this means that P + 1 < Q.

The function should return the number of arithmetic slices in the array A.

 
Example:

A = [1, 2, 3, 4]

return: 3, for 3 arithmetic slices in A: [1, 2, 3], [2, 3, 4] and [1, 2, 3, 4] itself.
*/


class Solution {
public:
	int numberOfArithmeticSlices(vector<int>& A) {
		if (A.size() < 3) return 0;
		
		int count = 0, group = 2, diff = A[1]-A[0];
		for (int i = 2; i < A.size(); i++) {
			int curDiff = A[i] - A[i-1];
			if (curDiff == diff) group++;
			else {
				count += countSlices(group);
				group = 2, diff = curDiff;
			}
		}
		count += countSlices(group);
		return count;
	}
	
	int countSlices(int x) {
		if (x < 3) return 0;
		int n = (x * (x+1)) / 2; // total substrings
		n -= (x + x-1); // remove 1,2 length substrings
		return n;
	}
};





class Solution {
public:
	int numberOfArithmeticSlices(vector<int>& A) {
		int n = A.size();
		if (n < 3) return 0;
		vector<int> dp(n, 0); // dp[i] means the number of arithmetic slices ending with A[i]
		if (A[2]-A[1] == A[1]-A[0]) dp[2] = 1; // if the first three numbers are arithmetic or not
		int result = dp[2];
		for (int i = 3; i < n; ++i) {
			// if A[i-2], A[i-1], A[i] are arithmetic, then the number of arithmetic slices ending with A[i] (dp[i])
			// equals to:
			//	  the number of arithmetic slices ending with A[i-1] (dp[i-1], all these arithmetic slices appending A[i] are also arithmetic)
			//	  +
			//	  A[i-2], A[i-1], A[i] (a brand new arithmetic slice)
			// it is how dp[i] = dp[i-1] + 1 comes
			if (A[i]-A[i-1] == A[i-1]-A[i-2]) 
				dp[i] = dp[i-1] + 1;
			result += dp[i]; // accumulate all valid slices
		}
		return result;
	}
};




class Solution {
public:
	int numberOfArithmeticSlices(vector<int>& A) {
		int n = A.size();
		if (n < 3) return 0;
		
		int prev = 0;
		if (A[2]-A[1] == A[1]-A[0]) prev = 1;
		int result = prev;
		
		for (int i = 3; i < n; ++i) {
			int cur = 0;
			if (A[i]-A[i-1] == A[i-1]-A[i-2]) {
				cur = prev + 1;
			}
			result += cur;
			prev = cur;
		}
		
		return result;
	}
};
