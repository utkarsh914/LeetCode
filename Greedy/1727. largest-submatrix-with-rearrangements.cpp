// https://leetcode.com/problems/largest-submatrix-with-rearrangements/

/*
You are given a binary matrix matrix of size m x n,
and you are allowed to rearrange the columns of the matrix in any order.

Return the area of the largest submatrix within matrix
where every element of the submatrix is 1 after reordering the columns optimally.

Example 1:

Input: matrix = [[0,0,1],[1,1,1],[1,0,1]]
Output: 4
Explanation: You can rearrange the columns as shown above.
The largest submatrix of 1s, in bold, has an area of 4.
*/





/*
1. For each column, find the number of consecutive ones ending at each position.
2. For each row, sort the cumulative ones in non-increasing order
	and "fit" the largest submatrix.
*/
class Solution {
public:
	int largestSubmatrix(vector<vector<int>>& M) {
		int R = M.size(), C = M[0].size();
		for (int i = 1; i < R; i++) {
			for (int j = 0; j < C; j++) {
				if (M[i][j] == 1) M[i][j] += M[i-1][j];
			}
		}

		int ans = 0;
		for (auto& r : M) {
			sort(r.begin(), r.end(), greater<int>());
			for (int i = 0, min_ = INT_MAX; i < C; i++) {
				min_ = min(min_, r[i]);
				ans = max(ans, min_ * (i+1));
			}
		}

		return ans;
	}
};