//https://leetcode.com/problems/valid-sudoku/

class Solution {
public:
	bool isValidSudoku(vector<vector<char>>& board) {
		unordered_set<string> seen;
		for (int i=0; i<board.size(); i++) {
			for (int j=0; j<board[0].size(); j++) {
				if (board[i][j] == '.') continue;
				string c(board[i][j], 1);
				string in_row = c + " in row " + to_string(i);
				string in_col = c + " in col " + to_string(j);
				string in_block = c + " in block " + to_string(i/3) + "-" + to_string(j/3);
				if (seen.count(in_row) or seen.count(in_col) or seen.count(in_block))
					return false;
				seen.insert(in_row);
				seen.insert(in_col);
				seen.insert(in_block);
			}
		}
		return true;
	}
};