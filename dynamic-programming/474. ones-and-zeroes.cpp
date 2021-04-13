// https://leetcode.com/problems/ones-and-zeroes/

/*
You are given an array of binary strings strs and two integers m and n.
Return the size of the largest subset of strs such that there are at most m 0's and n 1's in the subset.
A set x is a subset of a set y if all elements of x are also elements of y.


Example 1:

Input: strs = ["10","0001","111001","1","0"], m = 5, n = 3
Output: 4
Explanation: The largest subset with at most 5 0's and 3 1's is {"10", "0001", "1", "0"}, so the answer is 4.
Other valid but smaller subsets include {"0001", "1"} and {"10", "1", "0"}.
{"111001"} is an invalid subset because it contains 4 1's, greater than the maximum of 3.
*/

class Solution {
	int dp[601][101][101];
public:
	int findMaxForm(vector<string>& strs, int m, int n) {
		memset(dp, -1, sizeof(dp));
		return find(strs, 0, m, n);
	}
	
	int find(vector<string>& A, int start, int m, int n) {
		if (start == A.size()) return 0;
		if (dp[start][m][n] != -1) return dp[start][m][n];
		
		int nz = 0, no = 0;
		for (char c : A[start]) {
			nz += c == '0';
			no += c == '1';
		}
		
		int take = 0, notTake = 0;
		notTake = find(A, start+1, m, n);
		if (nz <= m && no <= n) take = 1 + find(A, start+1, m-nz, n-no);
		
		return dp[start][m][n] = max(take, notTake);
	}
};








class Solution {
public:
	int findMaxForm(vector<string>& A, int M, int N) {
		int dp[601][101][101] = {};
		int s = A.size();

		for (int i=s-1; i >= 0; i--) {
			// count zeros and ones in curr string
			int nz = 0, no = 0;
			for (char c : A[i]) {
				nz += c == '0';
				no += c == '1';
			}
			// if (nz > M or no > N) continue;

			for (int m=0; m <= M; m++) {
				for (int n=0; n <= N; n++) {
					int take = (nz <= m && no <= n) ? 1 + dp[i+1][m-nz][n-no] : 0;
					int notTake = dp[i+1][m][n];
					dp[i][m][n] = max(take, notTake);
				}
			}
		}

		return dp[0][M][N];
	}
};







class Solution {
public:
	int findMaxForm(vector<string>& A, int M, int N) {
		int dp[2][101][101] = {};
		int s = A.size();

		for (int i=s-1; i >= 0; i--) {
			// count zeros and ones in curr string
			int nz = 0, no = 0;
			for (char c : A[i]) {
				nz += c == '0';
				no += c == '1';
			}

			for (int m=0; m <= M; m++) {
				for (int n=0; n <= N; n++) {
					int take = (nz <= m && no <= n) ? 1 + dp[(i+1)%2][m-nz][n-no] : 0;
					int notTake = dp[(i+1)%2][m][n];
					dp[i%2][m][n] = max(take, notTake);
				}
			}
		}

		return dp[0][M][N];
	}
};