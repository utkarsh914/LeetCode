// https://leetcode.com/problems/sudoku-solver/

class Solution {
public:
	void solveSudoku(vector<vector<char>>& B) {
		backtrack(B, 0);
	}

	bool backtrack(vector<vector<char>>& B, int cell) {
		// completed
		if (cell >= 81) return true;

		int x = cell / 9, y = cell % 9;

		// proceed to next iteration if curr char is already set
		if (B[x][y] != '.')
			return backtrack(B, cell+1);
		
		// one by one try every possible number
		// if any number completes the board, return true
		for (char c = '1'; c <= '9'; c++) {
			if (canPlace(B, c, x, y)) {
				B[x][y] = c;
				if (backtrack(B, cell+1))
					return true;
				B[x][y] = '.';
			}
		}

		return false;
	}


	bool canPlace(vector<vector<char>>& B, char c, int x, int y) {
		// check in cur row
		for (int j = 0; j < 9; j++)
			if (B[x][j] == c) return false;

		// check in cur col
		for (int i = 0; i < 9; i++)
			if (B[i][y] == c) return false;

		// check in cur block
		x = (x/3)*3, y = (y/3)*3;
		for (int i = x; i < x + 3; i++)
			for (int j = y; j < y + 3; j++)
				if (B[i][j] == c) return false;
		
		return true;
	}

};











/*
***** similar to n-queen *****

this can be used to find all valid sudoku arrangements
where no number is filled already
*/
class Solution {
	vector<vector<char>> board;
public:
	void solveSudoku(vector<vector<char>>& B) {
		backtrack(B, 0);
		B = board;
	}

	void backtrack(vector<vector<char>>& B, int ind = 0) {
		// completed
		if (ind >= 81) {
			board = B;
			return;
		}

		int x = ind / 9, y = ind % 9;

		if (B[x][y] != '.') {
			backtrack(B, ind+1);
			return;
		}
		
		for (char c = '1'; c <= '9'; c++) {
			if (canPlace(B, c, x, y)) {
				B[x][y] = c;
				backtrack(B, ind+1);
				B[x][y] = '.';
			}
		}
	}


	bool canPlace(vector<vector<char>>& B, char c, int x, int y) {
		// check in cur row
		for (int j = 0; j < 9; j++)
			if (B[x][j] == c) return false;

		// check in cur col
		for (int i = 0; i < 9; i++)
			if (B[i][y] == c) return false;

		// check in cur block
		x = (x/3)*3, y = (y/3)*3;
		for (int i = x; i < x + 3; i++)
			for (int j = y; j < y + 3; j++)
				if (B[i][j] == c) return false;
		
		return true;
	}

};