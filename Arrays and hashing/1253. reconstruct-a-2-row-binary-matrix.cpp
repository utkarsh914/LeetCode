// https://leetcode.com/problems/reconstruct-a-2-row-binary-matrix/

class Solution {
public:
	vector<vector<int>> reconstructMatrix(int upper, int lower, vector<int>& colSum) {
		
		int C = colSum.size();
		int up = upper, low = lower;
		vector<vector<int>> M(2, vector<int> (C, 0));

		for (int j = 0; j < C; j++) {
			if (colSum[j] == 2) {
				M[0][j] = M[1][j] = 1;
				up--, low--;
			}
		}

		for (int j = 0; j < C; j++) {
			if (colSum[j] != 1) continue;
			if (up > 0) M[0][j] = 1, up--;
			else M[1][j] = 1, low--;
		}

		int myUpperSum = accumulate(M[0].begin(), M[0].end(), 0);
		int myLowerSum = accumulate(M[1].begin(), M[1].end(), 0);

		return (myLowerSum == lower and myUpperSum == upper) ?
			M : vector<vector<int>>();
	}
};




/*
Intuition:

If the column sum is 2 or 0, the choice is obvius.

If it's 1, we set the upper bit if upper is larger than lower, and lower bit otherwise
*/
// SIMPLER
vector<vector<int>> reconstructMatrix(int u, int l, vector<int>& cs) {
	vector<vector<int>> res(2, vector<int>(cs.size()));
	for (auto i = 0; i < cs.size(); u -= res[0][i], l -= res[1][i++]) {
		res[0][i] = cs[i] == 2 || (cs[i] == 1 && l < u);
		res[1][i] = cs[i] == 2 || (cs[i] == 1 && !res[0][i]);
	}
	return u == 0 && l == 0 ? res : vector<vector<int>>();
}