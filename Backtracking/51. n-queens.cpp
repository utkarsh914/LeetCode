// https://leetcode.com/problems/n-queens/


/*
In this problem, we can go row by row,
and in each position, we need to check
if the column, the 45° diagonal and the 135° diagonal
had a queen before.
*/

class Solution {
	vector<vector<string>> ans;
	vector<string> B;
	int n;

public:
	vector<vector<string>> solveNQueens(int n) {
		this->n = n;
		B.resize(n, string(n, '.'));
		backtrack(0);
		return ans;
	}


	void backtrack(int row) {
		if (row == n) {
			ans.push_back(B);
			return;
		}

		// try placing a queen in every col of this row
		for (int col = 0; col < n; col++) {
			if (canPlace(row, col)) {
				B[row][col] = 'Q'; // place queen here
				backtrack(row + 1);
				B[row][col] = '.'; // revert current changes
			}
		}
	}


	bool canPlace(int x, int y) {
		int dr[] = {-1,-1,-1};
		int dc[] = {-1, 0, 1};

		for (int k = 0; k < 3; k++) {
			int r = x+dr[k], c = y+dc[k];
			while (r>=0 && r<n && c>=0 && c<n) {
				if (B[r][c] == 'Q') return false;
				r = r+dr[k], c = c+dc[k];
			}
		}
		
		return true;
	}
};


















class Solution {
	vector<vector<string>> ans;
	vector<string> B;
	int n;

public:
	vector<vector<string>> solveNQueens(int n) {
		this->n = n;
		B.resize(n, string(n, '.'));
		backtrack(n, 0);
		return ans;
	}


	bool backtrack(int k, int ind) {
		if (ind >= n*n) {
			if (k == 0) {
				this->ans.push_back(B);
				return true;
			}
			return false;
		}

		int x = ind / n, y = ind % n;
		bool ans = false;

		// place queen here
		if (canPlace(x, y)) {
			B[x][y] = 'Q';
			if (backtrack(k-1, ind+1)) ans = true;
		}
		// don't place queen here
		B[x][y] = '.';
		if (backtrack(k, ind+1)) ans = true;
		
		// revert current changes (backtrack)
		B[x][y] = '.';
		return ans;
	}


	bool canPlace(int x, int y) {
		
		int dr[] = {-1,-1,-1, 0};
		int dc[] = {-1, 0, 1,-1};

		for (int k = 0; k < 4; k++) {
			int r = x+dr[k], c = y+dc[k];
			while (r>=0 && r<n && c>=0 && c<n) {
				if (B[r][c] == 'Q') return false;
				r = r+dr[k], c = c+dc[k];
			}
		}
		
		return true;
	}
};
