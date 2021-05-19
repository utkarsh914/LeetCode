// https://leetcode.com/problems/find-valid-matrix-given-row-and-column-sums/

class Solution {
public:
	vector<vector<int>> restoreMatrix(vector<int>& rowSum, vector<int>& colSum) {
		int R = rowSum.size(), C = colSum.size();
		vector<vector<int>> M(R, vector<int> (C, 0));

		// initialize first col with row sums
		for (int i = 0; i < R; i++) {
			M[i][0] = rowSum[i];
		}

		// iterate through every column (except last)
		// and shift unneeded amount to the right column
		for (int j = 0; j < C-1; j++) {
			int sum = colSum[j];
			for (int i = 0; i < R; i++) {
				if (M[i][j] <= sum) {
					sum -= M[i][j];
				}
				else {
					M[i][j+1] += M[i][j] - sum;
					M[i][j] = sum, sum = 0;
				}
			}
		}

		return M;
	}
};